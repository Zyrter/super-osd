; Various fonts.
; 8xN (8 bits per row) and 16xN (16 bits per row) fonts
; are supported. Structures store font information.

.section rdonly,psv

; Font #1, a small 5x5 font stored in 8xN format.
.global		font1
font1:		.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x00
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x01
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x02
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x03
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x04
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x05
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x06
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x07
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x08
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x09
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x0a
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x0b
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x0c
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x0d
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x0e
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x0f
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x10
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x11
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x12
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x13
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x14
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x15
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x16
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x17
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x18
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x19
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x1a
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x1b
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x1c
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x1d
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x1e
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x1f
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x20
			.byte 0x20, 0x20, 0x20, 0x00, 0x20  ; char #0x21
			.byte 0x50, 0x50, 0x00, 0x00, 0x00  ; char #0x22
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x23
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x24
			.byte 0xc8, 0xd0, 0x20, 0x58, 0x98  ; char #0x25
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x26
			.byte 0x20, 0x20, 0x00, 0x00, 0x00  ; char #0x27
			.byte 0x10, 0x20, 0x20, 0x20, 0x10  ; char #0x28
			.byte 0x20, 0x10, 0x10, 0x10, 0x20  ; char #0x29
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x2a
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x2b
			.byte 0x00, 0x00, 0x00, 0x20, 0x40  ; char #0x2c
			.byte 0x00, 0x00, 0x70, 0x00, 0x00  ; char #0x2d
			.byte 0x00, 0x00, 0x00, 0x00, 0x30  ; char #0x2e
			.byte 0x08, 0x10, 0x20, 0x40, 0x80  ; char #0x2f
			.byte 0x70, 0xc8, 0xa8, 0x98, 0x70  ; char #0x30
			.byte 0x60, 0xa0, 0x20, 0x20, 0xf8  ; char #0x31
			.byte 0xf8, 0x08, 0xf8, 0x80, 0xf8  ; char #0x32
			.byte 0xf8, 0x08, 0xf8, 0x08, 0xf8  ; char #0x33
			.byte 0x88, 0x88, 0xf8, 0x08, 0x08  ; char #0x34
			.byte 0xf8, 0x80, 0xf8, 0x08, 0xf8  ; char #0x35
			.byte 0xf8, 0x80, 0xf8, 0x88, 0xf8  ; char #0x36
			.byte 0xf8, 0x08, 0x10, 0x20, 0x40  ; char #0x37
			.byte 0xf8, 0x88, 0xf8, 0x88, 0xf8  ; char #0x38
			.byte 0xf8, 0x88, 0xf8, 0x08, 0x08  ; char #0x39
			.byte 0x60, 0x60, 0x00, 0x60, 0x60  ; char #0x3a
			.byte 0x60, 0x60, 0x00, 0x60, 0x20  ; char #0x3b
			.byte 0x10, 0x20, 0x40, 0x20, 0x10  ; char #0x3c
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x3d
			.byte 0x40, 0x20, 0x10, 0x20, 0x40  ; char #0x3e
			.byte 0xf8, 0x08, 0x70, 0x00, 0x40  ; char #0x3f
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x40
			.byte 0x70, 0x88, 0xf8, 0x88, 0x88  ; char #0x41
			.byte 0xf0, 0x88, 0xf0, 0x88, 0xf0  ; char #0x42
			.byte 0x78, 0x80, 0x80, 0x80, 0x78  ; char #0x43
			.byte 0xf0, 0x88, 0x88, 0x88, 0xf0  ; char #0x44
			.byte 0xf8, 0x80, 0xf8, 0x80, 0xf8  ; char #0x45
			.byte 0xf8, 0x80, 0xf0, 0x80, 0x80  ; char #0x46
			.byte 0xf8, 0x80, 0xb8, 0x88, 0xf8  ; char #0x47
			.byte 0x88, 0x88, 0xf8, 0x88, 0x88  ; char #0x48
			.byte 0xf8, 0x20, 0x20, 0x20, 0xf8  ; char #0x49
			.byte 0xf8, 0x20, 0x20, 0x20, 0xe0  ; char #0x4a
			.byte 0x88, 0x90, 0xe0, 0x90, 0x88  ; char #0x4b
			.byte 0x80, 0x80, 0x80, 0x80, 0xf8  ; char #0x4c
			.byte 0xd8, 0xa8, 0xa8, 0xa8, 0xa8  ; char #0x4d
			.byte 0xc8, 0xa8, 0x98, 0x88, 0x88  ; char #0x4e
			.byte 0x70, 0x88, 0x88, 0x88, 0x70  ; char #0x4f
			.byte 0xf0, 0x88, 0xf0, 0x80, 0x80  ; char #0x50
			.byte 0xf0, 0x90, 0x90, 0xf0, 0x18  ; char #0x51
			.byte 0xf0, 0x88, 0xf0, 0xa0, 0x90  ; char #0x52
			.byte 0x78, 0x80, 0x70, 0x08, 0xf0  ; char #0x53
			.byte 0xf8, 0x20, 0x20, 0x20, 0x20  ; char #0x54
			.byte 0x88, 0x88, 0x88, 0x88, 0x70  ; char #0x55
			.byte 0x88, 0x88, 0x88, 0x50, 0x20  ; char #0x56
			.byte 0xa8, 0xa8, 0xa8, 0xa8, 0x50  ; char #0x57
			.byte 0x88, 0x50, 0x20, 0x50, 0x88  ; char #0x58
			.byte 0x88, 0x50, 0x20, 0x20, 0x20  ; char #0x59
			.byte 0xf8, 0x10, 0x20, 0x40, 0xf8  ; char #0x5a
			.byte 0x70, 0x40, 0x40, 0x40, 0x70  ; char #0x5b
			.byte 0x80, 0x40, 0x20, 0x10, 0x08  ; char #0x5c
			.byte 0x70, 0x10, 0x10, 0x10, 0x70  ; char #0x5d
			.byte 0x18, 0x18, 0x00, 0x00, 0x00  ; char #0x5e
			.byte 0x00, 0x00, 0x00, 0x00, 0xf8  ; char #0x5f
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x60
			.byte 0x70, 0x88, 0xf8, 0x88, 0x88  ; char #0x61
			.byte 0xf0, 0x88, 0xf0, 0x88, 0xf0  ; char #0x62
			.byte 0x78, 0x80, 0x80, 0x80, 0x78  ; char #0x63
			.byte 0xf0, 0x88, 0x88, 0x88, 0xf0  ; char #0x64
			.byte 0xf8, 0x80, 0xf8, 0x80, 0xf8  ; char #0x65
			.byte 0xf8, 0x80, 0xf0, 0x80, 0x80  ; char #0x66
			.byte 0xf8, 0x80, 0xb8, 0x88, 0xf8  ; char #0x67
			.byte 0x88, 0x88, 0xf8, 0x88, 0x88  ; char #0x68
			.byte 0xf8, 0x20, 0x20, 0x20, 0xf8  ; char #0x69
			.byte 0xf8, 0x20, 0x20, 0x20, 0xe0  ; char #0x6a
			.byte 0x88, 0x90, 0xe0, 0x90, 0x88  ; char #0x6b
			.byte 0x80, 0x80, 0x80, 0x80, 0xf8  ; char #0x6c
			.byte 0xd8, 0xa8, 0xa8, 0xa8, 0xa8  ; char #0x6d
			.byte 0xc8, 0xa8, 0x98, 0x88, 0x88  ; char #0x6e
			.byte 0xf8, 0x88, 0x88, 0x88, 0xf8  ; char #0x6f
			.byte 0xf0, 0x88, 0xf0, 0x80, 0x80  ; char #0x70
			.byte 0xf0, 0x90, 0x90, 0xf0, 0x18  ; char #0x71
			.byte 0xf0, 0x88, 0xf0, 0xa0, 0x90  ; char #0x72
			.byte 0x78, 0x80, 0x70, 0x08, 0xf0  ; char #0x73
			.byte 0xf8, 0x20, 0x20, 0x20, 0x20  ; char #0x74
			.byte 0x88, 0x88, 0x88, 0x88, 0x70  ; char #0x75
			.byte 0x88, 0x88, 0x88, 0x50, 0x20  ; char #0x76
			.byte 0xa8, 0xa8, 0xa8, 0xa8, 0x50  ; char #0x77
			.byte 0x88, 0x50, 0x20, 0x50, 0x88  ; char #0x78
			.byte 0x88, 0x50, 0x20, 0x20, 0x20  ; char #0x79
			.byte 0xf8, 0x10, 0x20, 0x40, 0xf8  ; char #0x7a
			.byte 0x30, 0x20, 0x40, 0x20, 0x30  ; char #0x7b
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x7c
			.byte 0x60, 0x20, 0x10, 0x20, 0x60  ; char #0x7d
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x7e
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x7f
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x80
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x81
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x82
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x83
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x84
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x85
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x86
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x87
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x88
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x89
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x8a
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x8b
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x8c
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x8d
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x8e
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x8f
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x90
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x91
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x92
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x93
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x94
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x95
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x96
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x97
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x98
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x99
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x9a
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x9b
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x9c
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x9d
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x9e
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0x9f
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa0
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa1
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa2
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa3
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa4
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa5
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa6
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa7
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa8
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xa9
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xaa
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xab
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xac
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xad
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xae
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xaf
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb0
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb1
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb2
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb3
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb4
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb5
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb6
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb7
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb8
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xb9
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xba
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xbb
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xbc
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xbd
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xbe
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xbf
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc0
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc1
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc2
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc3
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc4
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc5
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc6
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc7
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc8
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xc9
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xca
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xcb
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xcc
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xcd
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xce
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xcf
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd0
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd1
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd2
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd3
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd4
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd5
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd6
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd7
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd8
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xd9
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xda
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xdb
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xdc
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xdd
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xde
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xdf
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe0
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe1
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe2
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe3
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe4
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe5
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe6
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe7
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe8
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xe9
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xea
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xeb
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xec
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xed
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xee
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xef
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xf0
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xf1
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xf2
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xf3
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xf4
			.byte 0x00, 0x00, 0x00, 0x00, 0x00  ; char #0xf5
			.byte 0x00, 0x00, 0x00, 0x00, 0x70  ; char #0xf6
			.byte 0x00, 0x88, 0x50, 0x20, 0x00  ; char #0xf7
			.byte 0x00, 0x20, 0x50, 0x88, 0x00  ; char #0xf8
			.byte 0x00, 0xf8, 0x70, 0x20, 0x00  ; char #0xf9
			.byte 0x00, 0x20, 0x70, 0xf8, 0x00  ; char #0xfa
			.byte 0xb8, 0x20, 0x30, 0x20, 0x20  ; char #0xfb
			.byte 0xb8, 0x20, 0x38, 0x00, 0x00  ; char #0xfc
			.byte 0x00, 0xf8, 0xf8, 0xf8, 0x00  ; char #0xfd
			.byte 0x00, 0xf8, 0xf8, 0xf8, 0xf8  ; char #0xfe
			.byte 0xf8, 0xf8, 0xf8, 0xf8, 0xf8  ; char #0xff

; All font info structures are packed like this:
;   - 2 bytes for index
;   - 2 bytes for width
;   - 2 bytes for height
;   - 2 bytes for format (0 = 8xN, 1 = 16xN)
;   - 2 bytes pointer to font struct
; The reason for 2 byte integers is that it simplifies
; the code. Only a few bytes extra for each font are 
; used because of this.
.global		fontinfo
fontinfo:	.word	0, 5, 5, 0, font1

.end
