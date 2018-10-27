section         .text

                global          _start
_start:

                sub             rsp, 2 * 128 * 8                ; ��������� stack pointer �� ��� ������� �����
                mov             rcx, 128                        ; ����� ������� ����� (����� ���������� ��� ������)
                mov             rdi, rsp                        ; ������������� ����� ������� ����� � rdi (����������� ������ �����, � �� ���������� ��������)
                call            read_long                       ; ��������� ������ �����
                lea             rdi, [rsp + 128 * 8]            ; ������������� ����� ��� ������� �����
                call            read_long                       ; ��������� ������ �����
                mov             rsi, rdi                        ; ������ ������ ����� "������"
                mov             rdi, rsp                        ; ����� ������� �����(��������� ������� �� ������� ���������)
                call            sub_long_long                   ; ���������� ���������
                call            write_long                      ; ������� ���������
                mov             al, 0x0a                        ; ������������� � al ������ �������� ������
                call            write_char                      ; ������� ������ ����� ������

                jmp             exit                            ; ����� �� ���������

; ��������� ���� ������� �����
;    rdi -- ����� ������������ (������� �����)
;    rsi -- ����� ����������� (������� �����)
;    rcx -- ����� �������� ����� � qwords
; ���������:
;    �������� ���������� � �������� rdi
sub_long_long:
                push            rdi                             ; �������� ������� �������� ��������� � ����
                push            rsi                             ;
                push            rcx                             ;

                clc                                             ; ������ ���� �������� (CF)
.loop:
                mov             rax, [rsi]                      ; ��������� � rax �������� �������� qword �����������
                lea             rsi, [rsi + 8]                  ; ��������� � ���������� qword �����������
                sbb             [rdi], rax                      ; �� ���� ���� ���������... � ��������� ��������
                lea             rdi, [rdi + 8]                  ; ��������� � ���������� qword � �����������
                dec             rcx                             ; ��������� ����� (�������� ����� �������� ��������� � �����)
                
                jnz             .loop                           ; ������������ � ������ �����, ���� rcx > 0

                pop             rcx                             ; ���������� ������ ������ � ��������
                pop             rsi                             ;
                pop             rdi                             ;
                ret

; adds two long number
;    rdi -- address of summand #1 (long number)
;    rsi -- address of summand #2 (long number)
;    rcx -- length of long numbers in qwords
; result:
;    sum is written to rdi
add_long_long:
                push            rdi
                push            rsi
                push            rcx

                clc
.loop:
                mov             rax, [rsi]
                lea             rsi, [rsi + 8]                  ; ����������� ��������� �� ��������� qword ������� ���������� (������)
                adc             [rdi], rax                      ; �������� ������� qword ���� ����� � carry
                lea             rdi, [rdi + 8]                  ; ����������� ��������� � ������ ���������
                dec             rcx
                jnz             .loop
                
                pop             rcx
                pop             rsi
                pop             rdi
                ret

; adds 64-bit number to long number
;    rdi -- address of summand #1 (long number)
;    rax -- summand #2 (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    sum is written to rdi
add_long_short:
                push            rdi
                push            rcx
                push            rdx
                
                xor             rdx,rdx                         ; �������� �������� � rdx
.loop:
                add             [rdi], rax                      ; ���������� ������� qword �������� ����� � rax
                                                                ;   ������ ��������� (�� ������ ��������)
                                                                ;   �������� CF (����� �� ��������� �����)
                adc             rdx, 0                          ; ��������� � rdx(==0) CF
                mov             rax, rdx                        ; ������������� � rax �������� ����� (== CF)
                xor             rdx, rdx                        ; �������� �������� � rdx
                add             rdi, 8
                dec             rcx
                jnz             .loop
                
                pop             rdx
                pop             rcx
                pop             rdi
                ret

; multiplies long number by a short
;    rdi -- address of multiplier #1 (long number)
;    rbx -- multiplier #2 (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    product is written to rdi
mul_long_short:
                push            rax
                push            rdi
                push            rcx
                
                xor             rsi, rsi
.loop:
                mov             rax, [rdi]                      ; �������� �������� � rax (������� qword �������� �����) �� rbx
                mul             rbx
                add             rax, rsi                        ; ��������� � rax �������� rsi (carry �� ����������� ���� �����)
                adc             rdx, 0
                mov             [rdi], rax                      ; ���������� ��������� � ������� qword �������� �����
                add             rdi, 8
                mov             rsi, rdx                        ; ���������� � rsi ������ 32 ���� ����������� �����, (rdx == CF)
                dec             rcx
                jnz             .loop
                
                pop             rcx
                pop             rdi
                pop             rax
                ret

; divides long number by a short
;    rdi -- address of dividend (long number)
;    rbx -- divisor (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    quotient is written to rdi
;    rdx -- remainder
div_long_short:
                push            rdi
                push            rax
                push            rcx
                
                lea             rdi, [rdi + 8 * rcx - 8]        ; ������������� � rdi ����� ������� qword �������� �����
                xor             rdx, rdx

.loop:
                mov             rax, [rdi]
                div             rbx                             ; ����� rbx �� rax
                mov             [rdi], rax                      ; ���������� ���������� �������� � rdi
                sub             rdi, 8                          ; ��������� �� ���������� qword �������� �����
                dec             rcx
                jnz             .loop
                
                pop             rcx
                pop             rax
                pop             rdi
                ret

; assigns a zero to long number
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
set_zero:
                push            rax
                push            rdi
                push            rcx
                
                xor             rax, rax
                rep stosq                                       ; rep - ���������, ���� rcx > 0, �� ������ �������� --rcx 
                                                                ; stosq - ������������� �������� qword �� �������� ������ ������ rax(0)
                                                                ;         ��������� � ���������� qword (����������� rdi)

                
                pop             rcx
                pop             rdi
                pop             rax
                ret

; checks if a long number is a zero
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
; result:
;    ZF=1 if zero
is_zero:
                push            rax
                push            rdi
                push            rcx
                
                xor             rax, rax
                rep scasq                                       ; scasq - ���������� �������� rax � ������� qword � ������������� ����, ���� != 
                                                                ;         ��������� � ���������� qword (����������� rdi)

                
                pop             rcx
                pop             rdi
                pop             rax
                ret

; read long number from stdin
;    rdi -- location for output (long number)
;    rcx -- length of long number in qwords
read_long:
                push            rcx
                push            rdi
                
                call            set_zero                        ; ������������� ��� qword �������� ����� � 0
.loop:
                call            read_char                       ; ��������� ������ - ������ �������� �����
                or              rax, rax                        ; ������������� SF (���� ����������)
                js              exit                            ; ������� �� ���������, ���� SF == 1,  �.�. rax < 0
                cmp             rax, 0x0a                       ; �������� �� ���������� ����� ������ (EOL)
                je              .done                           ; ����������� ������ (������������� �� ����� .done), ���� �� ���������� ���� ==
                cmp             rax, '0'                        ; ��������� ������������ ���������� ������� (�����)
                jb              .invalid_char                   ; ���� �������� ���� <, ������������ ������ - ������� ������
                cmp             rax, '9'                        ; ���������� ��������� ������� �������
                ja              .invalid_char                   ;
                
                sub             rax, '0'                        ; �������� ��������� �������� ���������� �������
                mov             rbx, 10                         
                call            mul_long_short                  ; �������� ������� ������� ����� �� 10 (�������� � rbx) (��������� ������� ������)
                call            add_long_short                  ; ��������� ��������� ����� � �������� ��������
                jmp             .loop

.done:
                pop             rdi
                pop             rcx
                ret

.invalid_char:
                mov             rsi, invalid_char_msg           ; ����� ��������� �� ������
                mov             rdx, invalid_char_msg_size      ;
                call            print_string                    ;
                call            write_char                      ; ������� ������������ ������
                mov             al, 0x0a                        ; ������������� � al  ������ ����� �����
                call            write_char                      ; ������� al

.skip_loop:
                call            read_char                       ; ��������� ������ �� ������
                or              rax, rax
                js              exit
                cmp             rax, 0x0a
                je              exit
                jmp             .skip_loop

; write long number to stdout
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
write_long:
                push            rax
                push            rcx
                
                mov             rax, 20                         ; ������������� � rax 20 (������������ ����� 64-bit �����)
                mul             rcx                             ; ������� ������������ ����� ����������
                mov             rbp, rsp                        ; ��������� ������������ ��� ���������� ������������� �������� �����
                sub             rsp, rax                        ; ������������� rsi � ����� ������������ ��� ����� (����� ������������ ������� � ����������)
                
                mov             rsi, rbp

.loop:
                mov             rbx, 10
                call            div_long_short              ; ����� ������� ������� ����� �� �������� � rbx (������� ������� ������)
                add             rdx, '0'                    ; ������ ���������� ������� �� ��� ���, ��� ������ �������
                dec             rsi                         ; �������� rsi
                mov             [rsi], dl                   ; ���������� ������ (��������� 8 ��� �� rdx) � ������, �� ������� ��������� rsi
                call            is_zero                     ; ���������, ��� � ������� ������� ����� ��� �������� ��������� �������
                jnz             .loop                       ; �������, ���� ���������� �������

                mov             rdx, rbp
                sub             rdx, rsi                    ; ������������� rdx � ������� ������ ������ � rsi
                call            print_string                ; ������� ������� �����

                mov             rsp, rbp
                pop             rcx
                pop             rax
                ret

; read one char from stdin
; result:
;    rax == -1 if error occurs
;    rax \in [0; 255] if OK
read_char:
                push            rcx
                push            rdi
                
                sub             rsp, 1                      ; ����� ��� ������ �������
                xor             rax, rax                    ; ��� ���������� ������, syscall 0 == sys_read
                xor             rdi, rdi                    ; ��� ��������� �����������, rdi == 0 => stdin
                mov             rsi, rsp                    ; ������������� ������� ����� ������ � rsi
                mov             rdx, 1
                syscall                                     ; ��������� �����, ���������� ������� ����� rdx � rsi
                cmp             rax, 1                 
                jne             .error                      ; ����� �� ���������, ���� ���� != 0 (ZF)
                xor             rax, rax
                mov             al, [rsp]                   ; ������������� � al ���� �� ������ �� rsp
                add             rsp, 1                      ; ��������������� �������� rsp

                pop             rdi
                pop             rcx
                ret
.error:
                mov             rax, -1                     ; ������������� rax � -1, (������ ������)
                add             rsp, 1
                pop             rdi
                pop             rcx
                ret

; write one char to stdout, errors are ignored
;    al -- char
write_char:
                sub             rsp, 1
                mov             [rsp], al                   ; ��������� �������� al � ������, �� ������� ��������� rsp
                mov             rax, 1                      ; syscall 1 == sys_write
                mov             rdi, 1                      ; rdi == 1 => stdout
                mov             rsi, rsp                    ; ������������� ������� ����� ������ � rsi
                mov             rdx, 1
                syscall                                     ; ��������� �����, ����� �������(������) �� ������ rsi ����� rdx
                add             rsp, 1
                ret

; program exit point
exit:
                mov             rax, 60                     ; syscall 60 == sys_exit
                xor             rdi, rdi                    ; rdi == 0 => ��������� ����������� ��� ������
                syscall                                     ; ��������� �����, ����� �� ���������

; print string to stdout
;    rsi -- string
;    rdx -- size
print_string:
push            rax
                mov             rax, 1                      ; syscall 1 == sys_write
                mov             rdi, 1                      ; rdi == 1 => stdout
                syscall                                     ; ��������� �����, ����� �������(������) �� ������ rsi ����� rdx

                pop             rax
                ret

                section         .rodata
invalid_char_msg:
                db              "Invalid character: "
invalid_char_msg_size: equ             $ - invalid_char_msg