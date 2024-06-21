This project is dedicated to the research and development of the DSW algorithm for balancing binary trees. For its application purpose, a file system based on a binary tree was created. The file system will be used to store objects, which can be both files and directories, so they will be called "objects" (the sizes of objects are just numbers, the objects themselves are not created on the computer, but exist only in the program).

Description of the algorithm of the user's work with the program.
The user can use the following functionality of the program:
1) Adding new objects
a) The user selects item "1" in the menu
b) The user enters the name of the so-called superobject - relatively speaking, a directory with a maximum of two subobjects.
c) The program checks for the existence of such an object in the system. If the entered superobject does not exist, the user will be notified and returned to the main menu
d) If the superobject exists - the user can enter the name of the new object and the size (in bytes) that he wants to create.
e) After creating a new object, it is possible to repeat points a) and b) respectively
f) It is not possible to create new objects with the same name in one superobject

2) Deleting objects
a) The user selects item "2" of the menu
b) The user enters the name of the superobject in which the object to be deleted is located.
c) The program checks for the existence of such an object in the system. If the entered superobject does not exist, the user will be notified and returned to the main menu
d) If the entered superobject exists - the user enters the object to be deleted.
e) The program carries out checks corresponding to point c).
f) The program deletes the object and notifies the user

3) Derivation of the structure of the file system
a) The user selects item "3" in the menu
b) If the system is empty - the user will see the "ROOT" superobject, which is installed by default (does not take up space)
c) If the user has added objects to the ROOT superfile, they will see a visualization of the layers
d) The user can add any number of objects (but no more than two per object)



4) Balancing the system with the DSW algorithm
a) The user selects item "4" in the menu.
b) The program informs the user about sorting
c) The user can view the sorted system by selecting item "3" in the menu.

5) Saving data in a separate file after exiting the program
a) The user selects item "0" in the menu.
b) The program informs about the completion of work
c) The program saves the system created by the user to the file "filesystem.txt", where the object and its size are stored