## About

**tc-lexer** is a C++ interpreter for generating custom testcases based on a given template. It supports random integer and string generation.


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
`$var_name [modifier]`

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
*Note : `eol` prints moves cursor to next line*

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

#### Hold
*Accessing a variable generates new value for it. In order to get last generated value use* `hold` *keyword*

```
$x between 5 10
hold x
$y between 0 x
hold x
x times print y space
eol
```
