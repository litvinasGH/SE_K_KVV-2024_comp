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
	INT10GLOBAL DWORD 39
	INT20GLOBAL DWORD 1
	STR30GLOBAL BYTE 'контрольный   пример', 0
	BOOl40GLOBAL BYTE 1
	INT50GLOBAL DWORD 0
