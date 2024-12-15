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

.stack 4096
;=================== сегмент констант =========================
.const
	INT00GLOBAL DWORD 45
	BOOl10GLOBAL DWORD 1
	BOOl20GLOBAL DWORD 0
	INT30GLOBAL DWORD 76468
	INT40GLOBAL DWORD 1
	INT50GLOBAL DWORD 39
	STR60GLOBAL BYTE '1234567890', 0
	STR70GLOBAL BYTE 'контрольный   пример', 0
	INT80GLOBAL DWORD 0
