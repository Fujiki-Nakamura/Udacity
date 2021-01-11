# FSND-P2-ItemCatalog
## Setup VM
```
$ git clone git@github.com:udacity/fullstack-nanodegree-vm.git
$ cd fullstack-nanodegree-vm/vagrant
$ vagrant up
```
Check if the default VM is running by `vagrant status`. If it's running, you can login to the VM by `vagrant ssh` and see the `vagrant` directory mounted to `/vagrant` on the VM.

## Setup data
In the VM,
```
$ cd /vagrant
$ git clone https://github.com/Fujiki-Nakamura/FSND-P2-ItemCatalog.git
$ cd /vagrant/FSND-P2-ItemCatalog
$ sudo pip3 install -r requirements.txt
$ python3 test_data.py
```
You'll have dummy data with some dummy categories and items in the Database for testing the web application.

## Usage
In the directory `/vagrant/FSND-P2-ItemCatalog` on the VM,
```
$ python3 views.py
```
Then, you can access to the item catalog web application in `localhost:5000/`. You can add/edit/delete items and add categories.
To get response from the JSON endpoint, you can access to `localhost:5000/<catalog_id>/<item_id>/json`. For example, accessing `localhost:5000/1/2/json`, you'll get information of the item with id 2 in the category 2 in JSON.


## TODO
- [ ] Edit/Delete Category
- [ ] OAuth to use the JSON endpoint
