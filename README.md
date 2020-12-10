# CS 225 Final Project
## Team members: Ashley Yeah, Brandon Oh, Jeha Chung, Jinpyo Lee

### Overview of Dataset
We have obtained the data from the following link: *https://openflights.org/data.html*. From this link we used the airlines.dat and airports.dat which are represented as text files in the repository. The text files are each saved as routedata.txt and airports.txt. 

### How to compile 
*After compiling by typing make, you could type ./flihgts and the followings for more options*
* " -h": You will be able to see all the options.
* " -m" or " --": run busiest airport
* " -b": Run BFS
* " -l": This would give the landmark path of the default airports. To customize the inputs, you could put 3 IATA codes of the airports you would like to input prior to a space. There should be a space between each input.

### Testing
#### Overview
* Busiest Airport: GDB
* BFS, Lanmark Path: The test cases are located in the test folder
#### Dummy datasets
For the functions to run there are a few requirements for the datasets:
* The order of elements and details should follow the how it is indicated link provided earlier. 
* Unlike the elements in the link, each name does not have be in quotation marks. 
* A comma should not be included in any of the elements in both the datasets. 
* The elements of the datasets that include names should already be capilized if needed. (The functions are case-sensitive)
* Each elements should be divided by commas.
* Elements could be left blank if unavailable.



