  PUBLIC EightBitHistogram                        

  SECTION .text : CODE(2)                         
  THUMB                                           

EightBitHistogram         PUSH {R4-R12, LR}       
  MUL R0,R0,R1                                    
  MOV R12, #65536                                 
  CMP R0, R12                                     
  MOV R12, #0
  IT HS
  BHS Return                                      
  MOV R4,#0
  ADD R4, R0, R2                                  

Loop                                              
  LDRB  R1,[R2]                                   
  ADD R3,R1                                       
  ADD R3,R1                                       
  BL Count                                        
  SUB R3,R1                                       
  SUB R3,R1                                       
  ADD R2,R2,#1                                    
  CMP R2,R4                                       
  BNE Loop
  MOV R0,R3
  POP {R4-R12, PC}                                

Count
  LDRH R6,[R3]                                    
  ADD R6,R6,#1                                    
  STRH R6,[R3]
  MOV R6,#0                                       
  BX LR
  
Return                                            
  MOV R0,#0
  POP {R4-R12, PC}                                

  END