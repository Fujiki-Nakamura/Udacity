#!/usr/bin/env python3
import psycopg2 as psql


def create_view(db):
    q = '''
    CREATE OR REPLACE VIEW log_with_slug AS
    SELECT *, SUBSTR(path, 10, 100) as slug
    FROM log
    ;
    '''
    c = db.cursor()
    c.execute(q)
    db.commit()


def answer1(db):
    q = '''
    SELECT A.title, count(L.id) as count
    FROM articles as A LEFT JOIN log_with_slug as L ON A.slug = L.slug
    GROUP BY A.id
    ORDER BY count DESC
    LIMIT 3
    ;
    '''
    c = db.cursor()
    c.execute(q)
    results = c.fetchall()
    a = '\n'.join(['"{}" - {} views'.format(r[0], r[1]) for r in results])
    return a


def answer2(db):
    q = '''
    SELECT A.name, count(AL.id) as count
    FROM authors as A LEFT JOIN (
        SELECT A.author, L.id
        FROM articles AS A
        LEFT JOIN log_with_slug as L ON A.slug = L.slug
    ) AS AL on A.id = AL.author
    GROUP BY A.id
    ORDER BY count DESC
    LIMIT 3
    ;
    '''
    c = db.cursor()
    c.execute(q)
    results = c.fetchall()
    a = '\n'.join(['{} - {} views'.format(r[0], r[1]) for r in results])
    return a


def answer3(db):
    q = '''
    SELECT TO_CHAR(S.date, 'Mon DD, yyyy')
         , ROUND(S.rate_bad * 100, 1) as percent
    FROM (
        SELECT DATE(time) as date
             , SUM(CASE WHEN L.status LIKE '200%' THEN 1 ELSE 0 END)
               as count_ok
             , SUM(CASE WHEN L.status LIKE '404%' THEN 1 ELSE 0 END)
               as count_bad
             , COUNT(L.id) as count
             , CAST(SUM(CASE WHEN L.status LIKE '404%' THEN 1 ELSE 0 END)
                AS decimal) / COUNT(L.id) as rate_bad
        FROM log as L
        GROUP BY date
        ORDER BY date
    ) AS S
    WHERE S.rate_bad > 0.01
    ORDER BY date
    ;
    '''
    c = db.cursor()
    c.execute(q)
    results = c.fetchall()
    a = '\n'.join(['{} - {}%'.format(r[0], r[1]) for r in results])
    return a


def main():
    db = psql.connect(database='news')
    q1 = '1. What are the most popular three articles of all time?'
    q2 = '2. Who are the most popular article authors of all time?'
    q3 = '3. On which days did more than 1% of requests lead to errors?'
    create_view(db)
    a1 = answer1(db)
    a2 = answer2(db)
    a3 = answer3(db)
    questions = [q1, q2, q3]
    answers = [a1, a2, a3]
    for q, a in zip(questions, answers):
        print(q)
        print(a)
        print()

    for q, a in zip(questions, answers):
        with open('answers.txt', 'a') as f:
            print(q, file=f)
            print(a, file=f)
            print(file=f)


if __name__ == '__main__':
    main()
