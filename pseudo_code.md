```
Declare SIZE N

Generate CurrentID
If rank == 0
    President = 0
    Vice-Pres = 0
    
    If CurrentID % 2 == 0
        Presient Value = CurrentID 
        Vice-Pres Value = 1
    else
        President Value = 99998 
        Vice-Pres Value = CurrentID
        
    Send President and Vice-Pres rank and value to next process
    Recieve President and Vice-Pres rank and value
    Print President and Vice Pres rank and value

if rank != 0
    Recieve President and Vice-Pres rank and value
    Print rank and CurrentID
    
    If CurrentID % 2 == 0
        If CurrentID < President Value
            President = rank 
            President Value = CurrentID
    else
        if CurrentID > Vice-Pres Value 
            Vice-Pres = rank
            Vice-Pres Value = CurrentID
            
    if rank == N-1
        Send President and Vice-Pres rank and value to process 0
    else
        Send President and Vice-Pres rank and value to next process
```
 
