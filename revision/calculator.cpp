qs type : 
    input : string expression 
    output : calculated value
type 1: only +,- and braces:
    same as 4
    when ( is found call calculate(++i)
    when ) is found return cur_sum 
type 2: +,-,*,/, no braces
    same as 4 
        OR 
    stack operation
    put calculated vals in stack..final ans is sum of stack 
    when a operand is found, calculate() and update stack 
type 3: +,-,*,/, braces
    - same as 1 
type 4: +,-,*,/, but online query 
    same as 2, but to dynamically clculate the value, have cur_sum and cur_mult
    if operand is seen and op is + or -, 
        cur_sum += operand
        or cur_sum += -operand
        and cur_mult = operand or -operand
    if operand is seen and op is * or / or %,
        cur_sum = cur_sum - cur_mult + cur_mult (op) operand
        cur_mult = cur_mult (op) operand