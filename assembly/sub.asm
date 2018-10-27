section         .text

                global          _start
_start:

                sub             rsp, 2 * 128 * 8                ; переносим stack pointer на два длинных числа
                mov             rcx, 128                        ; длина первого числа (потом используем для циклов)
                mov             rdi, rsp                        ; устанавливаем адрес первого числа в rdi (переносится именно адрес, а не содержимое регистра)
                call            read_long                       ; считываем первое число
                lea             rdi, [rsp + 128 * 8]            ; устанавливаем адрес для второго числа
                call            read_long                       ; считываем второе число
                mov             rsi, rdi                        ; делаем второе число "вторым"
                mov             rdi, rsp                        ; адрес первого числа(вычитание зависит от порядка операндов)
                call            sub_long_long                   ; вычисление операндов
                call            write_long                      ; выводим результат
                mov             al, 0x0a                        ; устанавливаем в al символ переноса строки
                call            write_char                      ; выводим символ конца строки

                jmp             exit                            ; выход из программы

; вычитание двух длинных чисел
;    rdi -- адрес уменьшаемого (длинное число)
;    rsi -- адрес вычитаемого (длинное число)
;    rcx -- длина длинного числа в qwords
; результат:
;    разность сохранится в регистре rdi
sub_long_long:
                push            rdi                             ; сохраним текущие значения регистров в стек
                push            rsi                             ;
                push            rcx                             ;

                clc                                             ; чистим флаг переноса (CF)
.loop:
                mov             rax, [rsi]                      ; переносим в rax значение текущего qword вычитаемого
                lea             rsi, [rsi + 8]                  ; переходим к следующему qword вычитаемого
                sbb             [rdi], rax                      ; по сути само вычитание... с переносом значения
                lea             rdi, [rdi + 8]                  ; переходим к следующему qword в уменьшаемом
                dec             rcx                             ; уменьшаем длину (значение также является счетчиком в цикле)
                
                jnz             .loop                           ; возвращаемся в начало цикла, если rcx > 0

                pop             rcx                             ; возвращаем старые данные в регистры
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
                lea             rsi, [rsi + 8]                  ; передвигаем указатель на следующий qword второго слагаемого (адреса)
                adc             [rdi], rax                      ; сложение текущих qword двух чисел с carry
                lea             rdi, [rdi + 8]                  ; передвигаем указатель в первом слагаемом
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
                
                xor             rdx,rdx                         ; обнуляем значение в rdx
.loop:
                add             [rdi], rax                      ; складываем текущий qword длинного числа с rax
                                                                ;   второе слагаемое (на первой итерации)
                                                                ;   значение CF (далее до завершния цикла)
                adc             rdx, 0                          ; добавляем к rdx(==0) CF
                mov             rax, rdx                        ; устанавливаем в rax значение флага (== CF)
                xor             rdx, rdx                        ; обнуляем значение в rdx
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
                mov             rax, [rdi]                      ; умножаем значение в rax (текущий qword длинного числа) на rbx
                mul             rbx
                add             rax, rsi                        ; добавляем к rax значение rsi (carry от предыдущего шага цикла)
                adc             rdx, 0
                mov             [rdi], rax                      ; записываем результат в текущий qword длинного числа
                add             rdi, 8
                mov             rsi, rdx                        ; записываем в rsi первые 32 бита полученного числа, (rdx == CF)
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
                
                lea             rdi, [rdi + 8 * rcx - 8]        ; устанавливаем в rdi адрес первого qword длинного числа
                xor             rdx, rdx

.loop:
                mov             rax, [rdi]
                div             rbx                             ; делим rbx на rax
                mov             [rdi], rax                      ; возвращаем полученное значение в rdi
                sub             rdi, 8                          ; переходим на предыдущий qword длинного числа
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
                rep stosq                                       ; rep - повторяем, пока rcx > 0, на каждой итерации --rcx 
                                                                ; stosq - устанавливаем значение qword по текущему адресу равным rax(0)
                                                                ;         переходим к следующему qword (увеличиваем rdi)

                
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
                rep scasq                                       ; scasq - сравниваем значение rax с текущим qword и устанавливаем флаг, если != 
                                                                ;         переходим к следующему qword (увеличиваем rdi)

                
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
                
                call            set_zero                        ; устанавливаем все qword длинного числа в 0
.loop:
                call            read_char                       ; считываем символ - разряд длинного числа
                or              rax, rax                        ; устанавливаем SF (знак результата)
                js              exit                            ; выходим из программы, если SF == 1,  т.е. rax < 0
                cmp             rax, 0x0a                       ; проверка на достижение конца строки (EOL)
                je              .done                           ; заканчиваем чтение (перескакиваем на метку .done), если на предыдущем щаге ==
                cmp             rax, '0'                        ; проверяем корректность введенного символа (цифра)
                jb              .invalid_char                   ; если проверка дала <, некорректные данные - выводим ошибку
                cmp             rax, '9'                        ; аналогично проверяем верхнюю границу
                ja              .invalid_char                   ;
                
                sub             rax, '0'                        ; получаем численное значение считанного символа
                mov             rbx, 10                         
                call            mul_long_short                  ; умножаем текущее длинное число на 10 (значение в rbx) (добавляем младший разряд)
                call            add_long_short                  ; добавляем считанное число к текущему длинному
                jmp             .loop

.done:
                pop             rdi
                pop             rcx
                ret

.invalid_char:
                mov             rsi, invalid_char_msg           ; вывод сообщения об ошибке
                mov             rdx, invalid_char_msg_size      ;
                call            print_string                    ;
                call            write_char                      ; выводим некорректный символ
                mov             al, 0x0a                        ; устанавливаем в al  символ конца троки
                call            write_char                      ; выводим al

.skip_loop:
                call            read_char                       ; считываем символ из потока
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
                
                mov             rax, 20                         ; устанавливаем в rax 20 (максимальная длина 64-bit числа)
                mul             rcx                             ; считаем максимальную длину результата
                mov             rbp, rsp                        ; оставляем пространство для строкового представления длинного числа
                sub             rsp, rax                        ; устанавливаем rsi в конец пространства для числа (будем обрабатывать символы с последнего)
                
                mov             rsi, rbp

.loop:
                mov             rbx, 10
                call            div_long_short              ; делим текущее длинное число на значение в rbx (убираем младший разряд)
                add             rdx, '0'                    ; меняем полученный остаток на его код, для вывода символа
                dec             rsi                         ; уменшаем rsi
                mov             [rsi], dl                   ; записываем символ (последные 8 бит из rdx) в память, на которую указывает rsi
                call            is_zero                     ; проверяем, что в текущем длинном числе еще остались ненулевые разряды
                jnz             .loop                       ; прыгаем, если предыдущее неверно

                mov             rdx, rbp
                sub             rdx, rsi                    ; устанавливаем rdx в текущий размер строки в rsi
                call            print_string                ; выводим длинное число

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
                
                sub             rsp, 1                      ; место для одного символа
                xor             rax, rax                    ; тип системного вызова, syscall 0 == sys_read
                xor             rdi, rdi                    ; тип файлового дескриптора, rdi == 0 => stdin
                mov             rsi, rsp                    ; устанавливаем текущий адрес строки в rsi
                mov             rdx, 1
                syscall                                     ; системный вызов, считывание символа длины rdx в rsi
                cmp             rax, 1                 
                jne             .error                      ; выход из программы, если флаг != 0 (ZF)
                xor             rax, rax
                mov             al, [rsp]                   ; устанавливаем в al байт из памяти по rsp
                add             rsp, 1                      ; восстанавливаем значение rsp

                pop             rdi
                pop             rcx
                ret
.error:
                mov             rax, -1                     ; устанавливаем rax в -1, (маркер ошибки)
                add             rsp, 1
                pop             rdi
                pop             rcx
                ret

; write one char to stdout, errors are ignored
;    al -- char
write_char:
                sub             rsp, 1
                mov             [rsp], al                   ; переносим значение al в память, на которую указыкает rsp
                mov             rax, 1                      ; syscall 1 == sys_write
                mov             rdi, 1                      ; rdi == 1 => stdout
                mov             rsi, rsp                    ; устанавливаем текущий адрес строки в rsi
                mov             rdx, 1
                syscall                                     ; системный вызов, вывод символа(строки) по адресу rsi длины rdx
                add             rsp, 1
                ret

; program exit point
exit:
                mov             rax, 60                     ; syscall 60 == sys_exit
                xor             rdi, rdi                    ; rdi == 0 => программа завершилась без ошибок
                syscall                                     ; системный вызов, выход из программы

; print string to stdout
;    rsi -- string
;    rdx -- size
print_string:
push            rax
                mov             rax, 1                      ; syscall 1 == sys_write
                mov             rdi, 1                      ; rdi == 1 => stdout
                syscall                                     ; системный вызов, вывод символа(строки) по адресу rsi длины rdx

                pop             rax
                ret

                section         .rodata
invalid_char_msg:
                db              "Invalid character: "
invalid_char_msg_size: equ             $ - invalid_char_msg