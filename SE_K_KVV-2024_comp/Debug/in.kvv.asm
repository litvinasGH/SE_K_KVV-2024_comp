;========================= шапка ==============================
.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/standartLib.lib
	ExitProcess PROTO : DWORD

	EXTRN rusL: proc
	EXTRN OutputInt: proc
	EXTRN OutputChar: proc
	EXTRN InputInt: proc
	EXTRN strEq: proc
	EXTRN findWord: proc

.stack 4096
;=================== сегмент констант =========================
.const
	INT00GLOBAL DWORD 45
	BOOl10GLOBAL BYTE 1
	BOOl20GLOBAL BYTE 0
	INT30GLOBAL DWORD 76468
	INT40GLOBAL DWORD 1
	INT50GLOBAL DWORD 39
	STR60GLOBAL BYTE '1234567890', 0
	STR70GLOBAL BYTE 'контрольный   пример', 0
	INT80GLOBAL DWORD 0
;=================== сегмент данных ============================

.data
	buffer BYTE 256 dup(0)
	zfi0GLOBAL DWORD ?
	xMAIN DWORD ?
	yMAIN DWORD ?
	zMAIN DWORD ?
	saMAIN DWORD ?
	sbMAIN DWORD ?
	bMAIN DWORD ?
;=================== сегмент кода ==============================

.code

fi0GLOBAL PROC xfi0GLOBAL : DWORD, yfi0GLOBAL : DWORD

push xfi0GLOBAL

push xfi0GLOBAL

push yfi0GLOBAL
	pop eax
	pop ebx
	or eax, ebx
	push eax
	pop eax
	pop ebx
	and eax, ebx
	push eax
	pop zfi0GLOBAL
	push strEq
	jmp local0
local0:
	pop eax
	ret
fi0GLOBAL ENDP

main PROC
call rusL

push INT00GLOBAL
	pop zMAIN
	mov al, BOOl10GLOBAL
	push ax
	pop bMAIN
	mov al, BOOl20GLOBAL
	push ax
	pop bMAIN

push INT30GLOBAL
	pop xMAIN

push INT40GLOBAL
	pop xMAIN

push INT50GLOBAL
	pop xMAIN
	mov al, BOOl10GLOBAL
	push ax
	pop yMAIN
	push offset STR60GLOBAL
	pop saMAIN
	push offset STR60GLOBAL
	pop sbMAIN

push xMAIN

push zMAIN
	call fi0GLOBAL
	push eax

push fi0GLOBAL
	pop zMAIN
	push ecx
	push offset STR70GLOBAL
	call OutputChar
	pop ecx
	pop ecx
	push ecx
call InputInt
mov zMAIN, eax
	pop ecx
	mov al, BOOl10GLOBAL
	cmp al, 1
	jz m0
	jnz m1
	je m0
m0:

push zMAIN
	pop eax
	not eax
	push eax
	pop zMAIN
	push ecx
	push zMAIN
	call OutputInt
	pop ecx
	pop ecx
m1:
	push strEq
		jmp theend
theend:
	call ExitProcess
main ENDP
end main
;=============================================================
