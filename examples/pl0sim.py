import sys


class stack():
    innerstack = [-1 for _ in range(1024)]
    stacktop = 0


def pop(tstack):
    tstack.stacktop -= 1
    if tstack.stacktop < 0:
        print("pop when stack empty")
    return tstack.innerstack[tstack.stacktop]


def push(tstack, val):
    tstack.innerstack[tstack.stacktop] = val
    tstack.stacktop += 1


if __name__ == "__main__":
    fin = open(sys.argv[1], "r")
    mystack = stack()
    insmemory = []
    datamemory = [-1 for _ in range(1024)]
    PC = 0
    while True:
        line = fin.readline()
        if not line:
            break
        else:
            line = line.strip('\n')
            insmemory.append(line.split(" "))
    while True:
        tmp = insmemory[PC]
        if tmp[0] == "INT":
            if eval(tmp[1]) == 0:
                val = mystack.innerstack[mystack.stacktop-1]
                print("result:", val)
            else:
                break
        elif tmp[0] == "PUT":
            if len(tmp) != 2:
                print("put instruction without op")
            else:
                push(mystack, eval(tmp[1]))
        elif tmp[0] == "LD":
            if len(tmp) == 1:
                addr = pop(mystack)
                push(mystack, datamemory[addr])
            elif len(tmp) == 2:
                push(mystack, datamemory[eval(tmp[1])])
            else:
                print("LD instruction wrong use")
        elif tmp[0] == "ST":
            if len(tmp) == 1:
                addr = pop(mystack)
                value = pop(mystack)
                datamemory[addr] = value
            elif len(tmp) == 2:
                value = pop(mystack)
                datamemory[eval(tmp[1])] = value
            else:
                print("ST instruction wrong use")
        elif tmp[0] == "JMP":
            if len(tmp) == 1:
                addr = pop(mystack)
                PC = addr
                continue
            elif len(tmp) == 2:
                addr = eval(tmp[1])
                PC = addr
                continue
            else:
                print("JMP instruction wrong use")
        elif tmp[0] == "JPC":
            if len(tmp) == 2:
                flag = pop(mystack)
                if flag == 1:
                    PC = eval(tmp[1])
                    continue
            else:
                print("JPC instruction wrong use")
        elif tmp[0] == "ADD":
            lvalue = pop(mystack)
            r = pop(mystack)
            push(mystack, lvalue+r)
        elif tmp[0] == "SUB":
            lvalue = pop(mystack)
            r = pop(mystack)
            push(mystack, lvalue-r)
        elif tmp[0] == "MUL":
            lvalue = pop(mystack)
            r = pop(mystack)
            push(mystack, lvalue*r)
        elif tmp[0] == "DIV":
            lvalue = pop(mystack)
            r = pop(mystack)
            if r == 0:
                print("divide by zero")
            else:
                push(mystack, lvalue//r)
        elif tmp[0] == "EQ":
            lvalue = pop(mystack)
            r = pop(mystack)
            if lvalue == r:
                push(mystack, 1)
            else:
                push(mystack, 0)
        elif tmp[0] == "LE":
            lvalue = pop(mystack)
            r = pop(mystack)
            if lvalue <= r:
                push(mystack, 1)
            else:
                push(mystack, 0)
        elif tmp[0] == "GE":
            lvalue = pop(mystack)
            r = pop(mystack)
            if lvalue >= r:
                push(mystack, 1)
            else:
                push(mystack, 0)
        elif tmp[0] == "LT":
            lvalue = pop(mystack)
            r = pop(mystack)
            if lvalue < r:
                push(mystack, 1)
            else:
                push(mystack, 0)
        elif tmp[0] == "GT":
            lvalue = pop(mystack)
            r = pop(mystack)
            if lvalue > r:
                push(mystack, 1)
            else:
                push(mystack, 0)
        elif tmp[0] == "NOT":
            value = pop(mystack)
            if value == 1:
                push(mystack, 0)
            elif value == 0:
                push(mystack, 1)
            else:
                print("NOT instruction but stack not is not bool value")
        else:
            print("unrecognized instruction")
        PC += 1

