<h1>Welcome to miniGit</h1>
1. Download miniGit Repo ZIP file. 


2. Insert files into your favorite IDE


3. Initiate project using "g++ -std=c++17 driver.cpp miniGit.cpp" in terminal/commandline


4. Have multiple options:

- Add files to current commit:
  When you want to add a file to the miniGit repository OR you change a file that has already been added to miniGit and want to log your changes, you start by adding
  files to the current commit. Simply select this option and type in the specific file you changed or want to add to the commit.

- Remove files from current commit
  If you added a file to the current commit, but don't want to commit it anymore, can remove file from the current commit. Type in the filename as you would when 
  adding a file to the current commit.

- Commit files in current commit
  When ready to commit your files/edits to miniGit, select this option. Creates a version of your files that is stored locally in .miniGit folder.

- Checkout other version
  If want to revert to an older version of your project, use this option. Type in the version number you want to checkout (1 is the first commit you created)

- Print out all files commited and related version number
  More of a useful tool for understanding how the version control system works under the hood. Can also use to track which files have been commited to miniGit

5. Can cancel the current miniGit instantiation using option 6: Quit. This will close the current instantiation of miniGit!!
