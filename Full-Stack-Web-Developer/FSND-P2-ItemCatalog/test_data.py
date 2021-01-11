#!/usr/bin/env python3
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from models import Base, Category, Item
from config import DB_URL


engine = create_engine(DB_URL)
Base.metadata.bind = engine
Session = sessionmaker(bind=engine)
session = Session()


def main():
    n_categories = 5
    n_items = 5
    username = 'testuser'

    for category_i in range(n_categories):
        category = Category(
            name='test_category_{}'.format(category_i),
            username=username)
        session.add(category)
        session.commit()

        for item_i in range(n_items):
            desc = 'This is test item {} in category {}'.format(
                item_i, category_i)
            item = Item(
                name='test_item_{}-{}'.format(category_i, item_i),
                description=desc, category=category,
                username=username)
            session.add(item)
            session.commit()


if __name__ == '__main__':
    main()
