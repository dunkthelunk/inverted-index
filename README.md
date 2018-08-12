## Inverted Index
   An Inverted Index is a data structure used for fast full-text searches. The primary reason for writing this was to learn modern C++; picked up parser theory as a bonus

## Search Interface
  * Case insensitive
  * Complex queries can be constructed with '|', '&', and  '~'
  * Space between words is treated as '&'
  * Examples:
 ``` 
  attack ships fire orion
  Julius - caesar
  ((osman | nizam) ~ last) & (dollar | pound) 
```
## Build and Run
  ```
  cd build
  make clean
  make
  ./search
```

Input data already present in the repo are random texts downloaded from gutenberg. see src/util/get-rand-txts-from-gutenberg.py and resources/txts/index.txt. 

```
  Enter query string (Ctrl+D to exit) : sherlock~holmes
  Query as a Scheme expression: (~ sherlock holmes)
  2 results.

  Title : The History of England,  from the Accession of James II — Volume 2
  Author : Macaulay
  
  Title : The Brass Bowl
  Author : Louis Joseph Vance
```

![alt text](https://raw.githubusercontent.com/dunkthelunk/inverted-index/master/resources/inverted%20index.gif "")

## TODO
### TermRecord Operators
Because of the way operators are implemented, positions of all query words are not preserved. This can be fixed easily by implementing term record intersection, union and difference
