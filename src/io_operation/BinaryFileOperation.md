Accessing a binary file from a `C++` program (by not using the old C functions) requires 
firstly __attaching a stream__ variable to the `file`. 
The usual stream classes __ofstream__ (output file stream) and __ifstream__ (input file stream) 
are still the types of streams to use. A an additional type called an __fstream__ is provided 
which allows for files that can be written to and read from if this is a desirable property 
(in the design of _database type programs_, this is often the case).

Before any operation can take place on a file, it of course must be opened, and when you are 
finished with the file, it should be closed to avoid loss of data.

##  Opening a Stream

The `ifstream` and `ofstream` each have member functions named open which are used to attaching 
the stream to a _physical filename_ and opening the file for either reading or writing. The 
open member function also provides for a couple of optional arguments that are not often 
described. The most general prototype of this function is

```cpp
void open(const char *filename[, int mode][, int prot]);
```

The format that I've used indicates that the mode and prot arguments are optional.

The first argument is always the name of the file on the disk that the stream will be `attached to`. 
The const modifier is included so that a programmer can write the name of the file (inside 
double quotes) in the function call. The only tricky part about using the open member 
function is under DOS based systems (includes Windows) in which directories are separated 
by a \; recall that the backslash character has a special meaning in C++ strings.

The prot parameter is used to specify the protection (`permission`) of the file under multiuser 
operating systems such as __Unix__. It allows you to specify which users are allowed to 
look at this file. Under DOS/Windows, this parameter is never used. The mode parameter is 
usually left out when dealing with text files, but there are some very useful situations under 
binary files for which this parameter must be set. There are a number of options that can 
be given for this parameter. If you need to specify more than one of them simply place a 
vertical bar between them.

- `ios::in` This indicates that the stream will be used for input. This may seem redundant
   for `ifstreams `which are automatically marked for input when they are opened, but it has 
   to be used occasionally. When you call open with no second parameter, the parameter is 
   assumed to be `ios::in` but if you give any other parameter such as `ios::binary` you will 
   need to specify that the file is an input file as well.
- `ios::out` This indicates that the stream will be used for output. Like `ios::in` this may 
   seem redundant for `ofstreams` but for the same reason as above, it usually has to be given.
- `ios::ate` This causes the file pointer to point  `at the end` of the file when the file is _opened_.
- `ios::trunc `This causes the all the existing data in the file to be `discarded (erased)` when 
   the file is opened. Be very careful not to use this option on a file you do not want destroyed!
- `ios::binary` This causes the file to be accessed as a _binary file_. Most likely you will need 
   to set this option. If you forget to set this option, many strange problems will occur when 
   reading certain characters like `end of line' and `end of file'.
   
Example of opening a binary file: 

```cpp
int main()
{
  ifstream infile;
  infile.open("hello.dat", ios::binary | ios::in);
// rest of program

}
```

## Writing to a Binary File

I mentioned once that `<<` is used to write data to a text file. If you had a variable `x` 
that contained the value `354` and you used the statement `outfile << x`; this would cause 
the character `3`, the character `5`, and the character `4` to be written (in __ASCII form__) 
to the file. This is not binary form which would only require `16-bits`. The `ofstream` class 
provides a member function named `write` that allows for information to be written in __binary__ 
form to the stream. The prototype of the write function is

```cpp
ostream& write(void *buffer, streamsize n);
``` 

This function causes `n` bytes to be written from the memory location given by the buffer to the 
disk and moves the file pointer `ahead n bytes`.

The parameters types require a little bit of explanation. Even though the return type is 
`ofstream&` the return value is usually ignored by most programers. The buffer pointer is 
of type `void` this allows for any type of variable to be used as the first parameter. 
You should not be writing functions with void parameters, this is a very tricky part of programming. 
The type `streamsize` is simply a positive integer.

It is rare that you will know exactly how many bytes a particular variable is. To obtain this 
information, `C++` provides a macro (its like a function) named sizeof that takes exactly one 
parameter and returns the size of the parameter in terms of bytes required for storage.

Below is an example of using the `sizeof` macro to obtain the size of a variable and writing 
the contents of a variable to disk. Notice the use of a `structure` rather than a class; you 
should not use this method for writing classes to binary files! See the section entitled 
`Writing Classes to Files` for a description of how this should be done.

```cpp
struct Person
{
  char name[50];
  int age;
  char phone[24];
};

int main()
{
  Person me = {"Robert", 28, "364-2534"};
  Person book[30];
  int x = 123;
  double fx = 34.54;
  ofstream outfile;
  outfile.open("junk.dat", ios::binary | ios::out);
  outfile.write(&x, sizeof(int)); // sizeof can take a type
  outfile.write(&fx, sizeof(fx)); // or it can take a variable name
  outfile.write(&me, sizeof(me));
  outfile.write(book, 30*sizeof(Person))
  outfile.close();
}
```

##  Reading from a Binary File

Reading data from a binary file is just like writing it except that the function is now called 
read instead of write When reading data from a file there are a couple of new things to 
watch out for:

- It is the responsibility of the programmer to make sure that the buffer is large enough to hold 
  all the data that is being read. The following code segment would probably result in a crash 
  unless the size of a integer was 7 bytes (unlikely number):
  
  ```cpp
   int main()
    {
      int x;
      ifstream infile;
      infile.open("silly.dat", ios::binary | ios::in)
      infile.read(&x, 7); // reads 7 bytes into a cell that is either 2 or 4
    }
  ```
- After reading something from the file, the `fail()` member function should be called to determine 
  if the operation completed successfully. In `C++`, no file operations cause the program to stop. 
  If an error occurs and you do not check it, then your program will be running unreliably. See a 
  section further in this document regarding the detection of errors.
  
## File Pointer

Whenever data is read from or writen to a file, the data is put or taken from a location inside the 
file described by the file pointer. In a sequential access file, information is always read from 
start to end and every time `n bytes` is read or written, the file pointer is moved n bytes ahead. 
In a random access file, we are allowed to moved the file pointer to different locations to read 
data at various locations within a file. Think of a database full of store items. When the item 
is scanned at the checkout, the barcode is used to look up a description and price of the item. 
If the file were sequential access, we would have to start searching at the beginning of the file 
which is probably slower than we would like. This is not a course in file processing, but it suffices 
to say that if we could move the file pointer directly to the record containing the data we would 
have to read from the file just once.

The `tellp()` member function has a prototype of the form
```cpp
streampos tellp(); // tell position
```

This function accepts no parameters, but returns the location given in bytes 
from the beginning of the file where the file pointer is currently sitting. The next read 
or write will take place from this location.

The `seekp()` member function has a prototype of the form
```cpp
void seekp(streampos location, int relative); // seek position
```
This causes the file pointer to move to another location within the file. The location specifies 
the number of bytes that will be used to determine the location and the relative parameter indicates 
whether this is some sort of absolute or relative positioning request. Possible values for relative 
are:

   1. ios::beg This indicates that the location is the number of bytes from the beginning of the file.
   2. ios::cur This indicates that the location is the number of bytes from the current file pointer location. This allows for a relative positioning of the file pointer.
   3. ios::end This indicates that the location is the number of bytes from the end of the file.
   
We consider an example that uses both obtaining and setting the file pointer location: 

```cpp
int main()
{
  int x;
  streampos pos;
  ifstream infile;
  infile.open("silly.dat", ios::binary | ios::in);
  infile.seekp(243, ios::beg); // move 243 bytes into the file
  infile.read(&x, sizeof(x));
  pos = infile.tellg();
  cout << "The file pointer is now at location " << pos << endl;
  infile.seekp(0,ios::end); // seek to the end of the file
  infile.seekp(-10, ios::cur); // back up 10 bytes
  infile.close();
} 
```

## Writing Classes to Binary Files

The easiest way to store records in files is to use astruct If you are keeping track of records in 
memory structures using classes, then saving these classes to disk takes a little extra work. 
You cannot simply use a write member function and give the address of the object as the buffer. 
The reason for this is the presence of member functions. It would not make sense to save the 
member functions; these member functions end up getting saved as memory locations which would 
cause your computer to crash if you ever loaded one from disk with an old memory location. It is 
possible to write objects to disk but it requires that the object have a member function associated 
with it.

My usual approach is to insert a member function named read and write in each member function. 
These functions should take an `fstream` as a parameter as the stream to save itself to. Your 
program should then open the stream and call the member function with the appropriate stream. 
The member function should then go through each data field of the object writing them out in 
a particular order. The read member function must retrieve the information from the disk in exactly 
the same order.

The example for this section is a little involved, so I've eliminated the non-file member functions. 
\begin{verbatim}

```cpp
#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>

class Student
{
  private:
    int number;
    char name[50];
    float gpa;
  public:
    Student(int n, const char *s, float g);
    void save(ofstream& of);
    void load(ifstream& inf);
};

main()
{
  Student me(11321, "Myself", 4.3);
  ofstream myfile;
  myfile.open("silly.dat", ios::binary | ios::out);
  me.save(myfile);
  myfile.close();
  return(0);
}

void Student::save(ofstream& of)
{
  of.write(&number, sizeof(number));
  of.write(name, sizeof(name));
  of.write(&gpa, sizeof(gpa));
}

void Student::load(ifstream& inf)
{
  inf.read(&number, sizeof(number));
  inf.read(name, sizeof(name));
  inf.read(&gpa, sizeof(gpa));
}
```

 
 
  
   
   

