# NOICETASK

## The Task

The Task has a Title, a Description, a Path, a Date when it was created, a Expire Date when it should be done, a Category, a Priority (from 1-3)

## Categories

It has a Title, maybe a Description (what it is for) and maybe a default Priority

## Priority

It goes from one to three, or from Low to Mid to High

## Functions

- [ ]  add Tasks: Adds an Task with the given Options to the Database
    * -t/--title: the Title for the Task (needed) => takes one String (maybe 90 Chars)
    * -d/--descripton: the Description body of the Task (optional) => takes a String (no limitation)
    * -pa/--path: the Path or File a Task is "linked" to (optional) => takes a String (gets checked)
    * -ex/--expire: the Date to when it needs to be done (optional) => takes a string (get converted to a timestamp)
    * -ca/--category: the Categories the Task belongs to (optional) => takes one String (gets checked, if not found create it??)
    * -pr/--priority: the Priority for the Task (optional -> default: 1) => takes a Int (1-3)

- [ ]  done Tasks: toggles the Done Status of a Task
    * -id: the id of the Task, which will be marked as done (needed) => takes one to n arguments (int)
    * (-ch/--choose: opens fzf with all Tasks which are not done => takes no arguments)

- [ ] mod Tasks: modifies a Task with the given Option and New Value
    * -id: the id of the Task, which will be modified (needed) => takes one (to n) argument (int)
    * -f/--field: the Option, which will be changed (needed) => takes one String
    * -nv/--newvalue: the New Value, which will be set for Option in Task (needed) => takes one String (maybe need splitting for this, see categories)

- [ ] remove Tasks: removes a Task from the Database
    * -id: the id of the Task, which will be removed (optional) => takes one to n arguments (int)
    * -m/--marked: removes all Tasks, which are marked as Done (optional) => takes no arguments
    * => one of them is needed!

- [ ] list: prints the given Database Table to screen in a Table (Tasks, Categoires, Paths) => default is Tasks
    * -t/--type: set the type of the output (optional -> default: Tasks) => takes a string (Task, category, path)
    * (maybe implementing search function -sf and -sv (searchfiled and value))

- [ ] add Category: adds an Category to the Database
    * -t/--title: the Title, which will get Displayed (needed) => takes a String (maybe max 40)
    * -d/--descripton: the Description for the Category (optional) => takes a String (no limitation)

- [ ] mod Category: modifies the given Category with the given Fileds and Values
    * -id: the id of the Category, which will be modified (needed) => takes one Int
    * -f/--field: the field, which will get changed (needed) => takes a string
    * -nv/--newvalue: the new value, which will be set for Field in Category (needed) => takes a string

- [ ] remove Category: removes a Category from the Database (maybe need to remove links in the Task database)
    * -id: the id of the Category, which gets removed (needed) => takes a int
