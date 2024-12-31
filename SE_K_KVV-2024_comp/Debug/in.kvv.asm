;========================= шапка ==============================
.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib standartLib.lib
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
	BOOl10GLOBAL BYTE 0
	INT20GLOBAL DWORD 39
	STR30GLOBAL BYTE '1234567890', 0
	INT40GLOBAL DWORD 1
	STR50GLOBAL BYTE 'контрольный    пример', 0
	BOOl60GLOBAL BYTE 1
	INT70GLOBAL DWORD 0
;=================== сегмент данных ============================

.data
	buffer BYTE 256 dup(0)
	zfi0GLOBAL DWORD ?
	xMAIN DWORD ?
	zMAIN DWORD ?
	saMAIN DWORD ?
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

push INT20GLOBAL
	pop xMAIN
	push offset STR30GLOBAL
	pop saMAIN

push xMAIN

push zMAIN
	call fi0GLOBAL
	push eax

push fi0GLOBAL

push INT40GLOBAL
	pop eax
	pop ebx
	and eax, ebx
	push eax
	pop zMAIN
	push ecx
	push offset STR50GLOBAL
	call OutputChar
	pop ecx
	pop ecx
	push ecx
call InputInt
mov zMAIN, eax
	pop ecx
	mov al, BOOl60GLOBAL
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
