;----------------------------------------------------
; CODE HIEU UNG BAN DAU
; CODE HIEU UNG AN MUNG
;----------------------------------------------------
$NOMOD51
$INCLUDE (80C52.MCU)
;----------------------------------------------------
      org  		0000h
      jmp  		Start
      ORG		0003H
      LJMP		INTER0
      org		0013h
      LJMP		INTER1

;----------------------------------------------------
      org   0100h
Start:	
      
      XUNG BIT	P2.0	; KHAI BAO CHAN:      XUNG
      CHOT	BIT	P2.2	; KHAI BAO CHAN :      CHOT
      DATA_B	BIT	P2.1	; KHAI BAO CHAN :      DATA_BLUE
      DATA_G	BIT	P2.3	;; KHAI BAO CHAN :      DATA_GREEN
      DATA_R	BIT	P2.4	; KHAI BAO CHAN :      DATA_RED
      ; POINT	P1 = R6
      MOV	R6, #00h
      MOV	P1, R6
      ; Write your code here
      SETB 	EA			;CHO PHEP CAC NGAT
      SETB	IT0			;CHO PHEP NHAT NGOAI  0 TICH CUC CANH
      SETB 	IT1			;CHO PHEP NGAT NGOAI 1 TICH CUC CANH
      SETB	EX0		;CHO PHEP NGAT NGOAI 0
      SETB 	EX1		;CHO PHEP NGAT NGOAI 1
      ;SETB	PX0		;U TIEN  NGAT NGOAI 0
      SETB	PX1		;UU TIEN NGAT NGOAI 1
      MOV 	R2, 	#150D		;R2 DE XAC DINH TIME DELAY TRONG TIMER
      JMP 		MENU
;----------------------------------------------------
MENU:
      NUT_KHOI_DONG:
      JNB 	P2.6, HIEU_UNG_KHOI_DONG
      JMP 	NUT_KHOI_DONG
      
 NUT_BAT_DAU:
      
	 MOV	R6, #00h 
	 MOV	P1,	#00h 
      CLR	DATA_G
      CLR	DATA_B
      JMP LOOP_MAIN
      
JMP MENU

;----------------------------------------------------

HIEU_UNG_KHOI_DONG:
L1:
MOV	R6, #00h 
MOV	P1, R6
 MOV 	R4, #4			;48 CON LED
LOOP1:
       SETB	DATA_B	 ;SANG DEN BLUE
       CLR		DATA_R
       CLR		DATA_G
       CLR 	XUNG		;TAO XUNG DE NAP DATA VAO IC595
       SETB 	XUNG		
               
      JNB P2.7, NUT_BAT_DAU 		;KIEM TRA NUT BAT DAU NEU DC NHAN THI JUMP

       DJNZ 	R4, 	LOOP1	; SET 48 BIT LEN ROI MOI CHOT
       
        CLR 	CHOT		;CHOT DU LIEU RA PORT
       SETB 	CHOT
       
       
       CALL DELAY1_2S
  MOV 	R4, #4			;48 CON LED
LOOP2:
	 CLR 	DATA_B	 ;SANG DEN BLUE
       SETB		DATA_R
       CLR		DATA_G
       
       CLR 	XUNG		;TAO XUNG DE NAP DATA VAO IC595
       SETB 	XUNG		
          
      JNB P2.7, NUT_BAT_DAU 		;KIEM TRA NUT BAT DAU NEU DC NHAN THI JUMP

       DJNZ 	R4, 	LOOP2	; SET 48 BIT LEN ROI MOI CHOT 
       
              CLR 	CHOT		;CHOT DU LIEU RA PORT
       SETB 	CHOT
    
         CALL DELAY1_2S
     MOV 	R4, #4
       LOOP3:
	 CLR 	DATA_B	 ;SANG DEN BLUE
       CLR		DATA_R
       SETB		DATA_G
       
       CLR 	XUNG		;TAO XUNG DE NAP DATA VAO IC595
       SETB 	XUNG		

          
      JNB P2.7, NUT_BAT_DAU 		;KIEM TRA NUT BAT DAU NEU DC NHAN THI JUMP

       DJNZ 	R4, 	LOOP3	; SET 48 BIT LEN ROI MOI CHOT
        CLR 	CHOT		;CHOT DU LIEU RA PORT
       SETB 	CHOT

     CALL DELAY1_2S
     JNB P2.7, NUT_BAT_DAU 		;KIEM TRA NUT BAT DAU NEU DC NHAN THI JUMP
 JMP	 HIEU_UNG_KHOI_DONG

 ;------------------------------------------------------------
LOOP_MAIN:

MOV 	R4, #48
LOOP222:
      CLR 		DATA_B	;TAT DEN BLUE
       CLR 	DATA_G	;TAT DEN GREEN
       CLR		DATA_R	;TAT DEN RED
       CLR		XUNG		
       SETB   	XUNG
       CLR		CHOT
      SETB	CHOT
       DJNZ 	R4, LOOP222

MOV 	R4, #48				; 48 DEN LED
LOOP6:
MOV	P1, R6
    L22:
      CLR		20H
      MOV		A, #01H; gia tri cho de xoay bit A = 1000 0000 BIN
      MOV		R0, #00D ; vi tri con led dang hien thi
      DOCBYTE:
	 MOV		R3, #48 ; 48 bit
      DOC_BIT:	 
	 CLR		C
	 RRC		A
	 MOV	DATA_R,   C
	 CLR	XUNG
	 SETB	XUNG ;tao xung de truyen du lieu
	     
	 MOV	B, 	A ; luu giu gia tri cua A lai sau nhieu buoc thay doi, luu vao B
	 CALL	DELAY1_2S
	 CLR	CHOT
	 SETB 	CHOT
	 INC	R0
	 DJNZ	R3, DOC_BIT
      JMP LOOP6
     ;-----------------------------------
INTER0:
CLR	 P2.7	;DE XAC DINH CO NHAY DEN NUT_BAT_DAU HAY KO
RETI
;----------------------------------------------------
INTER1:
MOV	P1, R6
   CJNE 	R0, #1D, SAI 	; VI TRI BAT = LED SO 10, NEU SAI THI NHAY DEN NHAN "SAI"
   
   TINH_DIEM:
	 MOV A, R6
	 ADD A, R6
	 INC A
	 MOV R6, A
	 MOV	P1, R6
    CJNE	R6, #15, NHANHLEN		;NEU BAT TRUNG THI DE NHAN "NHANHLEN"
      JMP	HIEU_UNG_FINAL		; NEU DIEM MAX THI HIEU UNG RIENG BIET
   
   SAI:
   JMP 	HIEU_UNG_SAI	
   NEXT:
   MOV 	R2, #150D	; RESET TOC DO
   
   KETTHUC: 
   MOV 		TMOD, 	#01		;SET LAI TIMER
   MOV		TH0, #0FCH
   MOV		TL0, #018H
   SETB	TR0
   RETI
   
    ;----------------------------------------------------
HIEU_UNG_SAI:

   MOV	R6, #00d
MOV	P1, R6
      MOV 	R5, #3D
 HIEU_UNG1:
    MOV 	R4, #48		; 48 CON LED
LOOP7:
       SETB	DATA_R
       CLR 	XUNG
       SETB 	XUNG

       DJNZ 	R4, LOOP7 	 ; SET 148BIT LEN ROI MOI CHOT 
       CLR 	CHOT
       SETB 	CHOT
       CALL	DELAY
       
       MOV 	R4, #48				; DEN DO CHOP TAT 3 LAN
LOOP8:
       CLR 	DATA_B
       CLR		DATA_R
       CLR		DATA_G
       CLR		XUNG
       SETB   	XUNG
       DJNZ 	R4, LOOP8
       CLR		CHOT
       SETB	CHOT
       CALL 	DELAY
DJNZ 	R5, HIEU_UNG1
JMP NEXT
   ;----------------------------------------------------
NHANHLEN:	
     MOV 	R5, #2D 		; LOOP 3 LAN
     
HIEU_UNG:
         MOV 	R4, #48			; 48 CON LED
LOOP9:
       SETB	DATA_B ; 1 BIT
       CLR	DATA_R
       CLR	DATA_G
       CLR 		XUNG
       SETB 	XUNG
       DJNZ 	R4, LOOP9	 ; SET 16 BIT LEN ROI MOI CHOT 
    	 CLR 	CHOT
       SETB 	CHOT
      CALL	DELAY
       
                MOV 	R4, #48; 16 CON LED
LOOP10:
       CLR		DATA_B ; 1 BIT
       SETB		DATA_R
       CLR		DATA_G
       CLR 	XUNG
       SETB 	XUNG

       DJNZ 	R4, LOOP10 ; SET 16 BIT LEN ROI MOI CHOT 
    	 CLR 	CHOT
       SETB 	CHOT
       CALL	DELAY
       
                       MOV 	R4, #48; 16 CON LED
LOOP11:
       CLR		DATA_B ; 1 BIT
       CLR		DATA_R
       SETB		DATA_G
       CLR 	XUNG
       SETB 	XUNG

       DJNZ 	R4, LOOP11 ; SET 16 BIT LEN ROI MOI CHOT 
    	 CLR 	CHOT
       SETB 	CHOT
       CALL	DELAY
DJNZ 	R5, HIEU_UNG 
 
                        MOV 	R4, #48; 1
  LOOP12:
       CLR		DATA_B ; 1 BIT
       CLR		DATA_R
       CLR		DATA_G
       CLR 	XUNG
       SETB 	XUNG

       DJNZ 	R4, LOOP12 ; SET 16 BIT LEN ROI MOI CHOT 
    	 CLR 	CHOT
       SETB 	CHOT
       CALL	DELAY
TANGTOC: 
      MOV 	A, R2
      SUBB 	A, #035D 
      MOV 	R2, A
      MOV		A, B
   JMP 	 KETTHUC


 ;----------------------------------------------------
HIEU_UNG_FINAL:
 MOV	R6, #00d
MOV	P1, R6
;=======TAT MAU TRUOC DO
MOV 	R4, #48
LOOP225:
      CLR 		DATA_B	;TAT DEN BLUE
       CLR 	DATA_G	;TAT DEN GREEN
       CLR		DATA_R	;TAT DEN RED
       CLR		XUNG		
       SETB   	XUNG
       CLR		CHOT
      SETB	CHOT
       DJNZ 	R4, LOOP225
;============= HIEU UNG FIANL
       MOV R5, #5
       LOOP51_1:
       CLR	DATA_B
	                        MOV 	R4, #48; 16 CON LED
LOOP51:
       CPL		DATA_B ; 1 BIT
       ;CLR		DATA_R
       ;SETB		DATA_G
       CLR 	XUNG
       SETB 	XUNG
      
       DJNZ 	R4, LOOP51 ; SET 16 BIT LEN ROI MOI CHOT 
       CLR 	CHOT
       SETB 	CHOT
              CALL	DELAY 
       
       
       SETB	DATA_B
        MOV 	R4, #48; 16 CON LED
LOOP51_2:
       CPL		DATA_B ; 1 BIT
       ;CLR		DATA_R
       ;SETB		DATA_G
       CLR 	XUNG
       SETB 	XUNG
      
       DJNZ 	R4, LOOP51_2 ; SET 16 BIT LEN ROI MOI CHOT 
       CLR 	CHOT
       SETB 	CHOT
              CALL	DELAY 
       DJNZ		R5, LOOP51_1
       
       
              	                        MOV 	R4, #48; 16 CON LED
LOOP51_3:
       CLR		DATA_G
       CLR		DATA_B
       CLR		DATA_R
       CLR 	XUNG
       SETB 	XUNG       
       DJNZ 	R4, LOOP51_3 ; SET 16 BIT LEN ROI MOI CHOT 
CLR 	CHOT
       SETB 	CHOT
       ;=====MAU DO
 

 
         MOV R5, #5
       LOOP52_1:
       CLR	DATA_R
	                        MOV 	R4, #48; 16 CON LED
LOOP52:
       CPL		DATA_R ; 1 BIT
       ;CLR		DATA_R
       ;SETB		DATA_G
       CLR 	XUNG
       SETB 	XUNG
      
       DJNZ 	R4, LOOP52 ; SET 16 BIT LEN ROI MOI CHOT 
       CLR 	CHOT
       SETB 	CHOT
              CALL	DELAY 
       
       
       SETB	DATA_R
        MOV 	R4, #48; 16 CON LED
LOOP52_2:
       CPL		DATA_R ; 1 BIT
       ;CLR		DATA_R
       ;SETB		DATA_G
       CLR 	XUNG
       SETB 	XUNG
      
       DJNZ 	R4, LOOP52_2 ; SET 16 BIT LEN ROI MOI CHOT 
       CLR 	CHOT
       SETB 	CHOT
              CALL	DELAY 
       DJNZ		R5, LOOP52_1
       
                     	                        MOV 	R4, #48; 16 CON LED
LOOP52_3:
       CLR		DATA_G
       CLR		DATA_B
       CLR		DATA_R
       CLR 	XUNG
       SETB 	XUNG       
       DJNZ 	R4, LOOP52_3 ; SET 16 BIT LEN ROI MOI CHOT 
CLR 	CHOT
       SETB 	CHOT
       ;=====MAU XANH LA
           MOV R5, #5
       LOOP53_1:
       CLR	DATA_G
	                        MOV 	R4, #48; 16 CON LED
LOOP53:
       CPL		DATA_G ; 1 BIT
       ;CLR		DATA_R
       ;SETB		DATA_G
       CLR 	XUNG
       SETB 	XUNG
      
       DJNZ 	R4, LOOP53 ; SET 16 BIT LEN ROI MOI CHOT 
       CLR 	CHOT
       SETB 	CHOT
              CALL	DELAY 
       
       
       SETB	DATA_G
        MOV 	R4, #48; 16 CON LED
LOOP53_2:
       CPL		DATA_G ; 1 BIT
       ;CLR		DATA_R
       ;SETB		DATA_G
       CLR 	XUNG
       SETB 	XUNG
      
       DJNZ 	R4, LOOP53_2 ; SET 16 BIT LEN ROI MOI CHOT 
       CLR 	CHOT
       SETB 	CHOT
              CALL	DELAY 
       DJNZ		R5, LOOP53_1
       
                     	                        MOV 	R4, #48; 16 CON LED
LOOP53_3:
       CLR		DATA_G
       CLR		DATA_B
       CLR		DATA_R
       CLR 	XUNG
       SETB 	XUNG       
       DJNZ 	R4, LOOP53_3 ; SET 16 BIT LEN ROI MOI CHOT 
CLR 	CHOT
       SETB 	CHOT
       ;==========
       
              	                        MOV 	R4, #48; 16 CON LED
LOOP50:
       CLR		DATA_G
       CLR		DATA_B
       ;CLR		DATA_R
       CLR 	XUNG
       SETB 	XUNG       
       DJNZ 	R4, LOOP50 ; SET 16 BIT LEN ROI MOI CHOT 
CLR 	CHOT
       SETB 	CHOT
              CALL	TIMER
   JMP NEXT 	 
       
 ;----------------------------------------------------
TIMER:					;TIMER 1 ms
     MOV 		TMOD, 	#01
      MOV		TH0, #0FCH
      MOV		TL0, #018H
      SETB	TR0
HERE1:		JNB 	TF0 ,HERE1
      CLR		TR0
      CLR		TF0
RET
;-----------------------------------------------------
DELAY1_2S:			;DELAY 0.5s DE THAY DOI SPEED
   MOV A, R2
   MOV R1, A
   LOOPDELAY1_2S:
	 CALL TIMER
	 DJNZ 	R1, LOOPDELAY1_2S
   MOV 		A, B

RET
;-----------------------------------------------------
DELAY1_22S:			;DELAY 0.5s DE THAY DOI SPEED
   MOV A, 50
   MOV R1, A
   LOOPDELAY1_22S:
	 CALL TIMER
	 DJNZ 	R1, LOOPDELAY1_22S
   MOV 		A, B

RET

;----------------------------------------------------------------------------
DELAY:                                              ; hàm DELAY  1s KO TIMER

						MOV	R3, #01
                                               MOV        10H, #01H       
                            AGAIN1:   MOV        11H, #0FFH       
                            AGAIN:     MOV        12H, #0FFH        
                            HERE:       DJNZ        12H, HERE       
                                               DJNZ        11H, AGAIN   
                                               DJNZ        10H, AGAIN1  
					    
                                               RET   
;====================================================================
      END

