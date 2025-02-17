# Thoughts 

## ToDo
- Test basic Version of Symbol table
- Add support for scope handling using a Hierarchial Symbol table design


## Ideas

### Handling `const`
- Things getting complicated with multilevel pointer const

### Handling Initialization Value
- After making initial version ask GPT any ideas

### For ID of Vardic Functions
    0+FunctName+argList {for overloading}
    1+FunctName
    

## Errors to Handle
 - While reading a assignment must chack if variable is non-const.
 - While inputing a const variable must make sure it's initialized
  - During Assignment must check if initialization value is capatible to symbol type
  - During function call must check if arguments are capatiable to locate functions
  - Storage Size of array must be known else it's compiler error