
### Lexer Level Error
- The ID of name 'f' is not being identified as ID. Fix it.


### Parser Level Error

- On-Spot use of Struct and Union is not being identified. Fix it.
Most likey it's comming for structHandler() and unionHandler() functions.

👍 FIXED

# ToDo
- Adjust Parse Tree such that any production of format A -> B  (i.e. UNIT Production) . The adding of child does not happen and B just transfer node to head of production A.
