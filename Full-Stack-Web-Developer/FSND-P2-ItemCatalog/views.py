#!/usr/bin/env python3
import json
import random
import string

from flask import Flask
from flask import (
    flash, jsonify, make_response, redirect, render_template,
    request, url_for)
from flask import session as login_session
import httplib2
from oauth2client.client import flow_from_clientsecrets, FlowExchangeError
from sqlalchemy import create_engine, desc
from sqlalchemy.orm import sessionmaker
import requests

from models import Base, Category, Item
from config import APP_SECRET_KEY, CLIENT_SECRETS, DB_URL


CLIENT_ID = json.loads(
    open(CLIENT_SECRETS, 'r').read())['web']['client_id']

engine = create_engine(DB_URL)
Base.metadata.bind = engine
Session = sessionmaker(bind=engine)
session = Session()

app = Flask(__name__)
app.secret_key = APP_SECRET_KEY


@app.route('/')
@app.route('/index')
def index():
    categories = session.query(Category).all()
    items = session.query(Item).order_by(desc(Item.id)).limit(10).all()
    return render_template('index.html', categories=categories, items=items)


@app.route('/login/')
def login():
    state = ''.join(random.choice(
        string.ascii_uppercase + string.digits) for _ in range(32))
    login_session['state'] = state
    return render_template('login.html', state=state)


@app.route('/gconnect', methods=['POST'])
def gconnect():
    if request.args.get('state') != login_session['state']:
        response = make_response(json.dumps('Invalid state parameter.'), 401)
        response.headers['Content-Type'] = 'application/json'
        return response

    code = request.data
    try:
        # Upgrade the authorization code into a credentials object
        oauth_flow = flow_from_clientsecrets(CLIENT_SECRETS, scope='')
        oauth_flow.redirect_uri = 'postmessage'
        credentials = oauth_flow.step2_exchange(code)
    except FlowExchangeError:
        response = make_response(
            json.dumps('Failed to upgrade the authorization code.'), 401)
        response.headers['Content-Type'] = 'application/json'
        return response

    # Check that the access token is valid.
    access_token = credentials.access_token
    url = ('https://www.googleapis.com/oauth2/v1/tokeninfo?access_token=%s'
           % access_token)
    h = httplib2.Http()
    result = json.loads(h.request(url, 'GET')[1].decode('utf-8'))
    # If there was an error in the access token info, abort.
    if result.get('error') is not None:
        response = make_response(json.dumps(result.get('error')), 500)
        response.headers['Content-Type'] = 'application/json'
        return response

    # Verify that the access token is used for the intended user.
    gplus_id = credentials.id_token['sub']
    if result['user_id'] != gplus_id:
        response = make_response(
            json.dumps("Token's user ID doesn't match given user ID."), 401)
        response.headers['Content-Type'] = 'application/json'
        return response

    # Verify that the access token is valid for this app.
    if result['issued_to'] != CLIENT_ID:
        response = make_response(
            json.dumps("Token's client ID does not match app's."), 401)
        response.headers['Content-Type'] = 'application/json'
        return response

    stored_access_token = login_session.get('access_token')
    stored_gplus_id = login_session.get('gplus_id')
    if stored_access_token is not None and gplus_id == stored_gplus_id:
        response = make_response(
            json.dumps('Current user is already connected.'), 200)
        response.headers['Content-Type'] = 'application/json'
        return response

    # Store the access token in the session for later use.
    login_session['access_token'] = credentials.access_token
    login_session['gplus_id'] = gplus_id
    # userinfo
    userinfo_url = "https://www.googleapis.com/oauth2/v1/userinfo"
    params = {'access_token': credentials.access_token, 'alt': 'json'}
    answer = requests.get(userinfo_url, params=params)
    data = answer.json()
    login_session['username'] = data['name']
    login_session['email'] = data['email']

    login_session['logged_in'] = True

    flash('Logged in successfully.')
    return redirect(url_for('index'))


@app.route('/logout/')
def logout():
    del login_session['access_token']
    del login_session['gplus_id']
    del login_session['username']
    del login_session['email']
    login_session['logged_in'] = False
    flash('Successfully logged out.')
    return redirect(url_for('index'))


@app.route('/catalog/<int:category_id>/')
def items(category_id):
    categories = session.query(Category).all()

    category = session.query(Category).filter_by(id=category_id).first()
    items = session.query(Item).filter_by(category_id=category_id).all()
    return render_template(
        'category.html', category_name=category.name, items=items,
        categories=categories)


@app.route('/catalog/<int:category_id>/<int:item_id>/')
def item(category_id, item_id):
    item = session.query(Item).filter_by(
        id=item_id, category_id=category_id).first()
    return render_template('item.html', item=item)


@app.route('/catalog/item/new', methods=['GET', 'POST'])
def create_item():
    if 'username' not in login_session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        name = request.form['name']
        description = request.form.get('description', '')
        category_name = request.form.get('category', '')
        category = session.query(Category).filter_by(
            name=category_name).first()
        item = Item(
            name=name, description=description, category_id=category.id,
            username=login_session['username'])
        session.add(item)
        session.commit()
        flash("Successfully created new item '{}'".format(item.name))
        return redirect(url_for('index'))
    else:
        categories = session.query(Category).all()
        return render_template('create_item.html', categories=categories)


@app.route('/catalog/category/new', methods=['GET', 'POST'])
def create_category():
    if 'username' not in login_session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        name = request.form['name']
        category = Category(name=name, username=login_session['username'])
        session.add(category)
        session.commit()
        flash("Successfully created new category '{}'".format(category.name))
        return redirect(url_for('index'))
    else:
        return render_template('create_category.html')


@app.route('/catalog/<int:category_id>/<int:item_id>/edit', methods=['GET', 'POST'])  # noqa
def edit_item(category_id, item_id):
    if 'username' not in login_session:
        return redirect(url_for('login'))
    categories = session.query(Category).all()
    category = session.query(Category).filter_by(id=category_id).first()
    item = session.query(Item).filter_by(
        id=item_id, category_id=category_id).first()

    if item.username != login_session['username']:
        flash('Permission denied.')
        return redirect(
            url_for('item', category_id=category_id, item_id=item_id))

    if request.method == 'POST':
        if request.form['name']:
            item.name = request.form['name']
        if request.form['description']:
            item.description = request.form['description']
        if request.form['category']:
            category_id = int(request.form['category'].split('. ')[0])
            item.category_id = category_id
        session.add(item)
        session.commit()
        return redirect('/catalog/{}/{}'.format(item.category_id, item.id))
    else:
        return render_template(
            'edit_item.html', item=item, category=category,
            categories=categories)


@app.route(
    '/catalog/<int:category_id>/<int:item_id>/delete',
    methods=['GET', 'POST'])
def delete_item(category_id, item_id):
    if 'username' not in login_session:
        return redirect(url_for('login'))
    category = session.query(Category).filter_by(id=category_id).first()
    item = session.query(Item).filter_by(
        id=item_id, category_id=category.id).first()

    if item.username != login_session['username']:
        flash('Permission denied.')
        return redirect(
            url_for('item', category_id=category_id, item_id=item_id))

    if request.method == 'POST':
        session.delete(item)
        session.commit()
        flash("Successfully deleted the item '{}'".format(item.name))
        return redirect(url_for('index'))
    else:
        return render_template(
            'delete_item.html', item=item, category=category)


@app.route('/catalog/<int:category_id>/<int:item_id>/json')
def json_endpoint(category_id, item_id):
    category = session.query(Category).filter_by(id=category_id).first()
    item = session.query(Item).filter_by(
        id=item_id, category_id=category.id).first()
    if item is None:
        flash('The requested URL was not found on the server.')
        return redirect(url_for('index'))
    return jsonify(Item=item.serialize)


if __name__ == '__main__':
    app.secret_key = APP_SECRET_KEY
    app.debug = True
    ip = '0.0.0.0'
    app.run(host=ip, port=5000)
