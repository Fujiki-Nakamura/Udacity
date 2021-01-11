# Logs Analysis

## Setup VM
```
$ git clone git@github.com:udacity/fullstack-nanodegree-vm.git
$ cd fullstack-nanodegree-vm/vagrant
$ vagrant up
```
Check if the default VM is running by `vagrant status`. If it's running, you can login to the VM by `vagrant ssh` and see the `vagrant` directory mounted to `/vagrant` on the VM.

## Setup logs
In the VM,
```
$ cd /vagrant
$ git clone https://github.com/Fujiki-Nakamura/FSND-P1-LogsAnalysis.git
$ cd FSND-P1-LogsAnalysis
$ wget https://d17h27t6h515a5.cloudfront.net/topher/2016/August/57b5f748_newsdata/newsdata.zip
$ unzip newsdata.zip
$ psql -d news -f newsdata.sql
```
You can check the database by `psql -d news`.

## Usage
In the `FSND-P1-LogsAnalysis` directory in the VM,
```
$ sudo pip3 install -r requirements.txt
$ python3 main.py
```

## Others
`main.py` creates a view named `log_with_slug` by function `create_view()` defined in it when it runs.
The view is created as below:
```
CREATE OR REPLACE VIEW log_with_slug AS
SELECT *, SUBSTR(path, 10, 100) as slug
FROM log
;
```
This will create a file named `answers.txt` which will contain the answers to the project's questions.
