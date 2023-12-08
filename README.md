## About

**tc-lexer** testcase generator for programming questions and competitions. It uses a C++ parser and generates testcases based on a given template. It supports random integer and string generation.

It can generate testcases like this:
```
4
6
110111
3
101
7
1001011
2
00
```
from this `random-binary-string-testcases.tc` template:
```
$T between 1 10
print T eol
$N between 1 10
$x between 0 2
T lines print N eol N times print x next x next N
```

## Features

- Random numbers within a range
- Random binary number within a range
- Random strings with random length

## Installation

You can get the latest release in the release section.

Navigate to the directory containing the executable open terminal

Run the following command to grant necessary permission:

```bash
$ chmod u+x lexer
```

## Usage

```bash
$ ./lexer < [template]
```

```bash
$ ./lexer < [template] > [output]
```

## Template Documentation


#### For declaring variables and adding modifiers:

```
$var_name [modifier]
```

Exmaples:
```
$x between 1 100
$x randomstring
$x uppercase
```

```
$y between 5 10
$y set 5
$y reset
```

#### For printing:
```
print y space print 5 eol
```

*Note : `print y` generates a new value for y*  
*Note : `space` prints exactly one space*  
*Note : `eol` moves cursor to next line*  

#### For looping:
To print value of variable x n times with a space in between
```
n times print x space
```
To print value of variable x in n lines
```
n lines print x
```
Or
```
n times print x eol
```

#### Next
To generate a new value for a variable, `next` keyword can be used

```
$x between 5 10
print x eol
$y between 0 x
x times print y space next y
eol
```

#### Strings

```
$x randomstring
$x between 5 10
$x toggled
print x
eol
```

```
$y randomstring
$x length 7
$x uppercase
$y set 5
y times print x eol
```
