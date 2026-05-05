bits 16              ; هنرجعه 16 بت عشان يشتغل بسهولة كـ Bootloader بيطبع OK
org 0x7c00           ; مكان التحميل في الذاكرة

start:
    mov ax, 0xb800   ; عنوان ذاكرة الفيديو
    mov es, ax
    
    ; طباعة حرف 'O' بلون أخضر
    mov byte [es:0x00], 'O'
    mov byte [es:0x01], 0x2f
    
    ; طباعة حرف 'K' بلون أخضر
    mov byte [es:0x02], 'K'
    mov byte [es:0x03], 0x2f

    jmp $            ; وقف الجهاز هنا

times 510-($-$$) db 0 
dw 0xAA55            ; التوقيع السحري