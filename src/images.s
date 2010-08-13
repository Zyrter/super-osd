; Static bitmapped images which may be blitted to the screen.
; Some images are compressed in different ways. Compression
; is relatively simple, usually just run length encoding.

.section rdonly,psv

; SuperOSD bootup logo.
; Consists of several frames.
.global logo_base
logo_base:	.byte	0xff, 0x00, 0x79, 0x00, 0x01, 0xc0, 0x01, 0x07 
			.byte	0x1e, 0x00, 0x01, 0x40, 0x01, 0x78, 0x1c, 0x00 
			.byte	0x01, 0x01, 0x01, 0x00, 0x02, 0xc0, 0x1c, 0x00 
			.byte	0x01, 0x03, 0x01, 0x00, 0x01, 0x80, 0x1d, 0x00 
			.byte	0x01, 0x02, 0x01, 0x00, 0x01, 0x80, 0x1d, 0x00 
			.byte	0x01, 0x06, 0x01, 0x00, 0x01, 0x80, 0x1d, 0x00 
			.byte	0x01, 0x04, 0x01, 0x00, 0x01, 0x80, 0x1d, 0x00 
			.byte	0x01, 0x08, 0x01, 0x00, 0x01, 0x80, 0x01, 0x01 
			.byte	0x08, 0x00, 0x01, 0x1f, 0x02, 0x00, 0x01, 0xc0 
			.byte	0x10, 0x00, 0x01, 0x08, 0x02, 0x00, 0x01, 0x01 
			.byte	0x08, 0x00, 0x01, 0xff, 0x01, 0x03, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x10, 0x00, 0x01, 0x10, 0x02, 0x00 
			.byte	0x01, 0x01, 0x08, 0x00, 0x01, 0xff, 0x01, 0x3f 
			.byte	0x01, 0xfe, 0x01, 0xff, 0x10, 0x00, 0x01, 0x10 
			.byte	0x02, 0x00, 0x01, 0x01, 0x08, 0x00, 0x01, 0xff 
			.byte	0x01, 0x7f, 0x02, 0xff, 0x01, 0x00, 0x01, 0x80 
			.byte	0x0e, 0x00, 0x01, 0x20, 0x02, 0x00, 0x01, 0x03 
			.byte	0x06, 0x00, 0x01, 0x01, 0x01, 0x00, 0x04, 0xff 
			.byte	0x01, 0x00, 0x01, 0xe0, 0x0e, 0x00, 0x01, 0x60 
			.byte	0x02, 0x00, 0x01, 0x02, 0x06, 0x00, 0x01, 0x07 
			.byte	0x01, 0x00, 0x04, 0xff, 0x01, 0x00, 0x01, 0xf8 
			.byte	0x0e, 0x00, 0x01, 0x40, 0x02, 0x00, 0x01, 0x02 
			.byte	0x06, 0x00, 0x01, 0x07, 0x01, 0x00, 0x04, 0xff 
			.byte	0x01, 0x00, 0x01, 0xfe, 0x0e, 0x00, 0x01, 0x80 
			.byte	0x02, 0x00, 0x01, 0x02, 0x06, 0x00, 0x01, 0x0f 
			.byte	0x01, 0x00, 0x04, 0xff, 0x01, 0x80, 0x01, 0xff 
			.byte	0x0e, 0x00, 0x01, 0x80, 0x01, 0x01, 0x01, 0x00 
			.byte	0x01, 0x04, 0x06, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0xe0, 0x01, 0xff, 0x0f, 0x00 
			.byte	0x01, 0x01, 0x01, 0x00, 0x01, 0x04, 0x06, 0x00 
			.byte	0x01, 0x0f, 0x01, 0x00, 0x04, 0xff, 0x01, 0xf8 
			.byte	0x01, 0xff, 0x0f, 0x00, 0x01, 0x02, 0x01, 0x00 
			.byte	0x01, 0x04, 0x06, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0xfc, 0x01, 0xff, 0x0f, 0x00 
			.byte	0x01, 0x02, 0x01, 0x00, 0x01, 0x04, 0x06, 0x00 
			.byte	0x01, 0x0f, 0x01, 0x00, 0x06, 0xff, 0x0a, 0x00 
			.byte	0x01, 0x01, 0x02, 0x00, 0x01, 0xe0, 0x01, 0x00 
			.byte	0x01, 0x04, 0x01, 0x00, 0x01, 0x08, 0x06, 0x00 
			.byte	0x01, 0x0f, 0x01, 0x00, 0x06, 0xff, 0x01, 0x00 
			.byte	0x01, 0xc0, 0x08, 0x00, 0x01, 0x06, 0x02, 0x00 
			.byte	0x01, 0x38, 0x01, 0x00, 0x01, 0x0c, 0x01, 0x00 
			.byte	0x01, 0x08, 0x06, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x08, 0x00 
			.byte	0x01, 0x38, 0x02, 0x00, 0x01, 0x07, 0x01, 0x00 
			.byte	0x01, 0x08, 0x01, 0x00, 0x01, 0x08, 0x06, 0x00 
			.byte	0x01, 0x03, 0x01, 0x00, 0x06, 0xff, 0x01, 0x00 
			.byte	0x01, 0xfc, 0x08, 0x00, 0x01, 0xe0, 0x01, 0x00 
			.byte	0x01, 0xe0, 0x02, 0x00, 0x01, 0x10, 0x01, 0x00 
			.byte	0x01, 0x08, 0x06, 0x00, 0x01, 0x01, 0x01, 0x00 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xff, 0x09, 0x00 
			.byte	0x01, 0x07, 0x01, 0x1c, 0x02, 0x00, 0x01, 0x30 
			.byte	0x01, 0x00, 0x01, 0x10, 0x08, 0x00, 0x01, 0xff 
			.byte	0x01, 0x7f, 0x04, 0xff, 0x01, 0xc0, 0x01, 0xff 
			.byte	0x09, 0x00, 0x01, 0x04, 0x01, 0x03, 0x02, 0x00 
			.byte	0x01, 0xa0, 0x01, 0x00, 0x01, 0x10, 0x08, 0x00 
			.byte	0x01, 0xff, 0x01, 0x1f, 0x04, 0xff, 0x01, 0xf0 
			.byte	0x01, 0xff, 0x09, 0x00, 0x01, 0x04, 0x03, 0x00 
			.byte	0x01, 0x40, 0x01, 0x00, 0x01, 0x10, 0x08, 0x00 
			.byte	0x01, 0xff, 0x01, 0x0f, 0x04, 0xff, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x09, 0x00, 0x01, 0x03, 0x03, 0x00 
			.byte	0x01, 0x40, 0x01, 0x00, 0x01, 0x10, 0x08, 0x00 
			.byte	0x01, 0xff, 0x01, 0x03, 0x04, 0xff, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x08, 0x00, 0x01, 0xc0, 0x04, 0x00 
			.byte	0x01, 0x80, 0x01, 0x00, 0x01, 0x20, 0x08, 0x00 
			.byte	0x01, 0xff, 0x01, 0x00, 0x06, 0xff, 0x01, 0x00 
			.byte	0x01, 0x80, 0x06, 0x00, 0x01, 0x30, 0x04, 0x00 
			.byte	0x01, 0x80, 0x01, 0x00, 0x01, 0x20, 0x08, 0x00 
			.byte	0x01, 0x3f, 0x01, 0x00, 0x04, 0xff, 0x01, 0x7f 
			.byte	0x01, 0xf8, 0x01, 0x00, 0x01, 0xe0, 0x06, 0x00 
			.byte	0x01, 0x18, 0x01, 0x00, 0x01, 0x01, 0x04, 0x00 
			.byte	0x01, 0xc0, 0x08, 0x00, 0x01, 0x1f, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0x0f, 0x01, 0xe0, 0x01, 0x00 
			.byte	0x01, 0xf8, 0x06, 0x00, 0x01, 0x06, 0x01, 0x00 
			.byte	0x01, 0x03, 0x01, 0x00, 0x01, 0x01, 0x02, 0x00 
			.byte	0x01, 0x80, 0x08, 0x00, 0x01, 0x07, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0x07, 0x01, 0xc3, 0x01, 0x00 
			.byte	0x01, 0xfe, 0x06, 0x00, 0x01, 0x01, 0x01, 0x00 
			.byte	0x01, 0x02, 0x01, 0x80, 0x01, 0x03, 0x02, 0x00 
			.byte	0x01, 0x80, 0x08, 0x00, 0x01, 0x01, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0xe1, 0x01, 0x87, 0x01, 0x80 
			.byte	0x01, 0xff, 0x08, 0x00, 0x01, 0x04, 0x01, 0x60 
			.byte	0x03, 0x00, 0x01, 0x70, 0x0a, 0x00, 0x04, 0xff 
			.byte	0x01, 0xf8, 0x01, 0x8f, 0x01, 0xe0, 0x01, 0xff 
			.byte	0x08, 0x00, 0x01, 0x04, 0x01, 0x18, 0x03, 0x00 
			.byte	0x01, 0x0e, 0x0a, 0x00, 0x01, 0xff, 0x01, 0x3f 
			.byte	0x02, 0xff, 0x01, 0xfc, 0x01, 0x8f, 0x01, 0xf8 
			.byte	0x01, 0xff, 0x08, 0x00, 0x01, 0x08, 0x01, 0x06 
			.byte	0x02, 0x00, 0x01, 0x80, 0x01, 0x03, 0x0a, 0x00 
			.byte	0x01, 0xff, 0x01, 0x0f, 0x03, 0xff, 0x01, 0xc7 
			.byte	0x01, 0xfe, 0x01, 0xff, 0x08, 0x00, 0x01, 0x88 
			.byte	0x01, 0x03, 0x02, 0x00, 0x01, 0x70, 0x0b, 0x00 
			.byte	0x01, 0xff, 0x01, 0x03, 0x03, 0xff, 0x01, 0xe1 
			.byte	0x02, 0xff, 0x01, 0x00, 0x01, 0x80, 0x06, 0x00 
			.byte	0x01, 0x10, 0x01, 0x1e, 0x02, 0x00, 0x01, 0x0e 
			.byte	0x0b, 0x00, 0x01, 0xff, 0x01, 0x01, 0x03, 0xff 
			.byte	0x01, 0xf0, 0x02, 0xff, 0x01, 0x00, 0x01, 0xe0 
			.byte	0x06, 0x00, 0x01, 0x30, 0x01, 0xf0, 0x02, 0x00 
			.byte	0x01, 0x01, 0x02, 0x00, 0x01, 0xc0, 0x08, 0x00 
			.byte	0x01, 0x7f, 0x01, 0x00, 0x02, 0xff, 0x01, 0x7f 
			.byte	0x01, 0xfc, 0x01, 0xff, 0x01, 0xcf, 0x01, 0x00 
			.byte	0x01, 0xf0, 0x04, 0x00, 0x01, 0x03, 0x01, 0x00 
			.byte	0x01, 0x20, 0x01, 0x80, 0x05, 0x00, 0x01, 0x70 
			.byte	0x08, 0x00, 0x01, 0x1f, 0x01, 0x00, 0x01, 0xe7 
			.byte	0x01, 0xff, 0x01, 0x3f, 0x01, 0xfe, 0x01, 0xff 
			.byte	0x01, 0x87, 0x01, 0x00, 0x01, 0xfc, 0x04, 0x00 
			.byte	0x01, 0x1c, 0x01, 0x00, 0x01, 0x40, 0x06, 0x00 
			.byte	0x01, 0x0e, 0x08, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x01, 0xe3, 0x01, 0xff, 0x01, 0x3f, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x01, 0x0f, 0x01, 0x00, 0x01, 0xff 
			.byte	0x04, 0x00, 0x01, 0xe0, 0x07, 0x00, 0x01, 0xc0 
			.byte	0x01, 0x01, 0x08, 0x00, 0x01, 0x03, 0x01, 0x00 
			.byte	0x01, 0xf0, 0x01, 0xff, 0x01, 0x3e, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x01, 0x1f, 0x01, 0xe0, 0x01, 0xff 
			.byte	0x05, 0x00, 0x01, 0x07, 0x03, 0x00, 0x01, 0x04 
			.byte	0x02, 0x00, 0x01, 0x38, 0x0b, 0x00, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x02, 0x3c, 0x01, 0xc7, 0x01, 0x3f 
			.byte	0x01, 0xf8, 0x01, 0xff, 0x05, 0x00, 0x01, 0x38 
			.byte	0x02, 0x00, 0x01, 0xc0, 0x01, 0x1f, 0x02, 0x00 
			.byte	0x01, 0x0e, 0x0b, 0x00, 0x01, 0xfe, 0x01, 0x3f 
			.byte	0x01, 0x7c, 0x01, 0x00, 0x01, 0x87, 0x01, 0x7f 
			.byte	0x01, 0xfe, 0x01, 0xff, 0x02, 0x00, 0x01, 0x01 
			.byte	0x02, 0x00, 0x01, 0xc0, 0x02, 0x00, 0x01, 0x3e 
			.byte	0x01, 0x60, 0x02, 0x00, 0x01, 0x01, 0x02, 0x00 
			.byte	0x01, 0xc0, 0x08, 0x00, 0x01, 0xff, 0x01, 0x1f 
			.byte	0x01, 0xf8, 0x01, 0xc0, 0x01, 0x0f, 0x03, 0xff 
			.byte	0x01, 0x00, 0x01, 0x80, 0x01, 0x0e, 0x03, 0x00 
			.byte	0x01, 0x01, 0x01, 0x00, 0x01, 0x03, 0x01, 0x80 
			.byte	0x01, 0x00, 0x01, 0xe0, 0x03, 0x00, 0x01, 0x30 
			.byte	0x08, 0x00, 0x01, 0xff, 0x01, 0x07, 0x01, 0xf0 
			.byte	0x01, 0xff, 0x01, 0x1f, 0x01, 0xfe, 0x02, 0xff 
			.byte	0x01, 0x00, 0x01, 0xe0, 0x01, 0x38, 0x03, 0x00 
			.byte	0x01, 0x06, 0x04, 0x00, 0x01, 0x1e, 0x03, 0x00 
			.byte	0x01, 0x60, 0x08, 0x00, 0x01, 0xff, 0x01, 0x01 
			.byte	0x01, 0xf1, 0x01, 0xff, 0x01, 0x3f, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x01, 0x9f, 0x01, 0x00, 0x01, 0xfc 
			.byte	0x01, 0xc0, 0x01, 0x01, 0x02, 0x00, 0x01, 0x18 
			.byte	0x03, 0x00, 0x01, 0xe0, 0x02, 0x01, 0x02, 0x00 
			.byte	0x01, 0x80, 0x08, 0x00, 0x01, 0xff, 0x01, 0x00 
			.byte	0x01, 0xf1, 0x01, 0xff, 0x01, 0x7f, 0x01, 0xf8 
			.byte	0x01, 0xff, 0x01, 0x0f, 0x01, 0x00, 0x01, 0xff 
			.byte	0x01, 0x00, 0x01, 0x0e, 0x02, 0x00, 0x01, 0x60 
			.byte	0x03, 0x00, 0x01, 0x1f, 0x01, 0x00, 0x01, 0x03 
			.byte	0x0b, 0x00, 0x01, 0x3f, 0x01, 0x00, 0x01, 0xf0 
			.byte	0x01, 0xff, 0x01, 0xfe, 0x01, 0xf0, 0x01, 0xff 
			.byte	0x01, 0x00, 0x01, 0xc0, 0x01, 0xff, 0x01, 0x00 
			.byte	0x01, 0x70, 0x02, 0x00, 0x01, 0x80, 0x01, 0x01 
			.byte	0x02, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x0c 
			.byte	0x01, 0xf0, 0x0a, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x01, 0xf8, 0x01, 0xff, 0x01, 0xfc, 0x01, 0x00 
			.byte	0x01, 0x7f, 0x01, 0x00, 0x01, 0xf1, 0x01, 0xff 
			.byte	0x01, 0x00, 0x01, 0x80, 0x03, 0x00, 0x01, 0x06 
			.byte	0x04, 0x00, 0x01, 0xf0, 0x01, 0x0f, 0x0a, 0x00 
			.byte	0x01, 0x07, 0x01, 0x00, 0x02, 0xff, 0x01, 0xf8 
			.byte	0x01, 0x21, 0x01, 0x3f, 0x01, 0x3e, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x05, 0x00, 0x01, 0x18, 0x04, 0x00 
			.byte	0x01, 0x80, 0x0b, 0x00, 0x01, 0x01, 0x01, 0x00 
			.byte	0x02, 0xff, 0x01, 0xf0, 0x01, 0xc3, 0x01, 0x1f 
			.byte	0x01, 0xfe, 0x02, 0xff, 0x01, 0x00, 0x01, 0x80 
			.byte	0x03, 0x00, 0x01, 0x60, 0x12, 0x00, 0x01, 0xff 
			.byte	0x01, 0x7f, 0x01, 0xf1, 0x01, 0xf7, 0x01, 0x1f 
			.byte	0x01, 0xfe, 0x02, 0xff, 0x01, 0x00, 0x01, 0xe0 
			.byte	0x01, 0x01, 0x02, 0x00, 0x01, 0x80, 0x12, 0x00 
			.byte	0x01, 0xff, 0x01, 0x1f, 0x01, 0xe1, 0x01, 0xff 
			.byte	0x01, 0x3f, 0x01, 0xfe, 0x02, 0xff, 0x01, 0x00 
			.byte	0x01, 0xf8, 0x01, 0x06, 0x15, 0x00, 0x01, 0xff 
			.byte	0x01, 0x0f, 0x01, 0xc1, 0x01, 0xff, 0x01, 0x3f 
			.byte	0x01, 0xfe, 0x02, 0xff, 0x01, 0x00, 0x01, 0xfe 
			.byte	0x01, 0x18, 0x15, 0x00, 0x01, 0xff, 0x01, 0x07 
			.byte	0x01, 0x81, 0x01, 0xff, 0x01, 0x3f, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x01, 0x00, 0x01, 0xc0, 0x01, 0xff 
			.byte	0x01, 0x60, 0x15, 0x00, 0x01, 0xff, 0x01, 0x04 
			.byte	0x01, 0x09, 0x01, 0xff, 0x01, 0x7c, 0x01, 0xf8 
			.byte	0x01, 0x7f, 0x01, 0x00, 0x01, 0xf0, 0x01, 0xff 
			.byte	0x01, 0x80, 0x01, 0x01, 0x14, 0x00, 0x01, 0x7f 
			.byte	0x01, 0x02, 0x01, 0x18, 0x01, 0xfe, 0x01, 0xf8 
			.byte	0x01, 0x00, 0x01, 0x1f, 0x01, 0x7e, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x01, 0x00, 0x01, 0x06, 0x14, 0x00 
			.byte	0x01, 0x1f, 0x01, 0x02, 0x01, 0x3e, 0x01, 0xfe 
			.byte	0x01, 0xf8, 0x01, 0x03, 0x01, 0x1f, 0x01, 0x3f 
			.byte	0x02, 0xff, 0x01, 0x00, 0x01, 0x18, 0x14, 0x00 
			.byte	0x01, 0x07, 0x01, 0x03, 0x01, 0x3f, 0x01, 0xfc 
			.byte	0x01, 0xf0, 0x02, 0x8f, 0x01, 0x0f, 0x02, 0xff 
			.byte	0x01, 0x00, 0x01, 0xe0, 0x14, 0x00, 0x02, 0x01 
			.byte	0x01, 0x7f, 0x01, 0xfe, 0x01, 0xf1, 0x01, 0xff 
			.byte	0x01, 0x8e, 0x01, 0xc3, 0x01, 0xff, 0x01, 0x7f 
			.byte	0x01, 0x00, 0x01, 0xf8, 0x15, 0x00, 0x01, 0x01 
			.byte	0x02, 0xff, 0x01, 0xf1, 0x01, 0xff, 0x01, 0x1c 
			.byte	0x01, 0xf0, 0x01, 0xff, 0x01, 0x3f, 0x01, 0x00 
			.byte	0x01, 0xfe, 0x14, 0x00, 0x01, 0x80, 0x01, 0x00 
			.byte	0x01, 0xff, 0x01, 0x3f, 0x01, 0xf1, 0x01, 0xff 
			.byte	0x01, 0x18, 0x01, 0xfc, 0x01, 0xff, 0x01, 0x07 
			.byte	0x01, 0xc0, 0x01, 0xff, 0x10, 0x00, 0x01, 0x0c 
			.byte	0x03, 0x00, 0x01, 0x80, 0x01, 0x00, 0x01, 0xff 
			.byte	0x01, 0x0f, 0x01, 0xf0, 0x01, 0xff, 0x01, 0x30 
			.byte	0x02, 0xff, 0x01, 0x01, 0x01, 0xf0, 0x01, 0xff 
			.byte	0x10, 0x00, 0x01, 0x14, 0x03, 0x00, 0x01, 0x80 
			.byte	0x01, 0x00, 0x01, 0xff, 0x01, 0x03, 0x01, 0xf8 
			.byte	0x01, 0xff, 0x01, 0xe1, 0x01, 0x7f, 0x01, 0xf0 
			.byte	0x01, 0xf9, 0x01, 0xfc, 0x01, 0x3f, 0x10, 0x00 
			.byte	0x01, 0x14, 0x03, 0x00, 0x01, 0x40, 0x01, 0x00 
			.byte	0x01, 0xff, 0x01, 0x07, 0x01, 0xfe, 0x01, 0xff 
			.byte	0x01, 0xc3, 0x01, 0x1f, 0x01, 0xc0, 0x02, 0xff 
			.byte	0x01, 0x07, 0x10, 0x00, 0x01, 0x14, 0x03, 0x00 
			.byte	0x01, 0x40, 0x01, 0x00, 0x01, 0x3f, 0x01, 0x18 
			.byte	0x02, 0xff, 0x01, 0xc7, 0x01, 0x83, 0x01, 0x07 
			.byte	0x02, 0xff, 0x01, 0xc3, 0x01, 0x00, 0x01, 0xe0 
			.byte	0x0e, 0x00, 0x01, 0x24, 0x03, 0x00, 0x01, 0x20 
			.byte	0x01, 0x00, 0x01, 0x07, 0x01, 0xe0, 0x02, 0xff 
			.byte	0x01, 0x87, 0x01, 0xf7, 0x01, 0x1f, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x01, 0xf1, 0x01, 0x00, 0x01, 0xf8 
			.byte	0x0e, 0x00, 0x01, 0x24, 0x03, 0x00, 0x01, 0x27 
			.byte	0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x02, 0xff 
			.byte	0x01, 0x0f, 0x01, 0xff, 0x01, 0x3f, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x01, 0xf8, 0x01, 0x00, 0x01, 0xfe 
			.byte	0x0e, 0x00, 0x01, 0x24, 0x03, 0x00, 0x01, 0x3c 
			.byte	0x03, 0x00, 0x01, 0xff, 0x01, 0x7f, 0x01, 0x1f 
			.byte	0x01, 0xfe, 0x01, 0x7f, 0x01, 0xfc, 0x01, 0x7f 
			.byte	0x01, 0xfc, 0x01, 0x80, 0x01, 0xff, 0x0e, 0x00 
			.byte	0x01, 0x24, 0x03, 0x00, 0x01, 0x60, 0x03, 0x00 
			.byte	0x01, 0xff, 0x01, 0x1f, 0x01, 0x3f, 0x02, 0xff 
			.byte	0x01, 0xf8, 0x01, 0x7f, 0x01, 0xfc, 0x01, 0xf0 
			.byte	0x01, 0xff, 0x0e, 0x00, 0x01, 0x42, 0x03, 0x00 
			.byte	0x01, 0x80, 0x01, 0x01, 0x02, 0x00, 0x01, 0xff 
			.byte	0x01, 0x07, 0x03, 0xff, 0x01, 0xf8, 0x01, 0x7f 
			.byte	0x02, 0xfc, 0x01, 0xff, 0x0e, 0x00, 0x01, 0x42 
			.byte	0x04, 0x00, 0x01, 0x06, 0x02, 0x00, 0x01, 0xff 
			.byte	0x01, 0x01, 0x03, 0xff, 0x01, 0xf0, 0x01, 0x7f 
			.byte	0x01, 0xf8, 0x01, 0xff, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x01, 0x80, 0x0c, 0x00, 0x01, 0x42, 0x04, 0x00 
			.byte	0x01, 0x38, 0x02, 0x00, 0x01, 0x7f, 0x01, 0x00 
			.byte	0x03, 0xff, 0x01, 0xf1, 0x01, 0xfc, 0x01, 0xf8 
			.byte	0x01, 0xff, 0x01, 0x01, 0x01, 0x00, 0x01, 0xe0 
			.byte	0x0c, 0x00, 0x01, 0x42, 0x04, 0x00, 0x01, 0xe0 
			.byte	0x02, 0x00, 0x01, 0x1f, 0x01, 0x00, 0x03, 0xff 
			.byte	0x02, 0xf8, 0x01, 0xf0, 0x01, 0xff, 0x01, 0x60 
			.byte	0x01, 0x00, 0x01, 0xf8, 0x0c, 0x00, 0x01, 0x42 
			.byte	0x01, 0x00, 0x01, 0x03, 0x02, 0x00, 0x01, 0x80 
			.byte	0x02, 0x00, 0x01, 0x07, 0x01, 0x00, 0x03, 0xff 
			.byte	0x01, 0xf8, 0x01, 0xf0, 0x01, 0xe1, 0x01, 0x3f 
			.byte	0x01, 0xfc, 0x01, 0x00, 0x01, 0xff, 0x0c, 0x00 
			.byte	0x01, 0x42, 0x01, 0x00, 0x01, 0x0c, 0x07, 0x00 
			.byte	0x02, 0xff, 0x01, 0x7f, 0x01, 0xfc, 0x01, 0xf1 
			.byte	0x01, 0xc3, 0x01, 0x1f, 0x01, 0xff, 0x01, 0xc0 
			.byte	0x01, 0xff, 0x0c, 0x00, 0x01, 0x42, 0x01, 0x00 
			.byte	0x01, 0x30, 0x07, 0x00, 0x01, 0xff, 0x01, 0x3f 
			.byte	0x01, 0x1f, 0x01, 0xfe, 0x01, 0xf1, 0x01, 0x07 
			.byte	0x01, 0x9f, 0x01, 0xff, 0x01, 0xf8, 0x01, 0xff 
			.byte	0x0c, 0x00, 0x01, 0x42, 0x01, 0x00, 0x01, 0xc0 
			.byte	0x07, 0x00, 0x01, 0xff, 0x01, 0xcf, 0x01, 0x80 
			.byte	0x01, 0xff, 0x01, 0xf8, 0x01, 0x0f, 0x02, 0xff 
			.byte	0x01, 0xfe, 0x01, 0x7f, 0x0c, 0x00, 0x01, 0x82 
			.byte	0x02, 0x00, 0x01, 0x03, 0x04, 0x00, 0x01, 0x03 
			.byte	0x01, 0x00, 0x01, 0xff, 0x01, 0x03, 0x01, 0xe0 
			.byte	0x01, 0xff, 0x01, 0xfc, 0x01, 0x7f, 0x01, 0xfe 
			.byte	0x01, 0x3f, 0x01, 0xff, 0x01, 0x1f, 0x01, 0x00 
			.byte	0x01, 0xc0, 0x0a, 0x00, 0x01, 0x82, 0x02, 0x00 
			.byte	0x01, 0x0c, 0x04, 0x00, 0x01, 0x0e, 0x01, 0x00 
			.byte	0x01, 0x7f, 0x01, 0x00, 0x02, 0xff, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x01, 0xfc, 0x01, 0x1f, 0x01, 0xff 
			.byte	0x01, 0x03, 0x01, 0x00, 0x01, 0xf0, 0x0a, 0x00 
			.byte	0x01, 0x82, 0x02, 0x00, 0x01, 0x70, 0x04, 0x00 
			.byte	0x01, 0x30, 0x01, 0x00, 0x01, 0x1f, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0xf8, 0x01, 0x8f, 0x01, 0xff 
			.byte	0x01, 0x61, 0x01, 0x00, 0x01, 0xfc, 0x0a, 0x00 
			.byte	0x01, 0x83, 0x02, 0x00, 0x01, 0xc0, 0x04, 0x00 
			.byte	0x01, 0xc0, 0x01, 0x00, 0x01, 0x07, 0x01, 0x00 
			.byte	0x03, 0xff, 0x01, 0xfc, 0x01, 0xf0, 0x01, 0xc7 
			.byte	0x01, 0x7f, 0x01, 0xf8, 0x01, 0x80, 0x01, 0xff 
			.byte	0x0a, 0x00, 0x01, 0x83, 0x08, 0x00, 0x01, 0x03 
			.byte	0x01, 0xff, 0x01, 0x03, 0x02, 0xff, 0x01, 0x7f 
			.byte	0x01, 0xfc, 0x01, 0xe1, 0x01, 0xc7, 0x01, 0x3f 
			.byte	0x01, 0xfe, 0x01, 0xe0, 0x01, 0xff, 0x0a, 0x00 
			.byte	0x01, 0x82, 0x07, 0x00, 0x01, 0xff, 0x01, 0x0e 
			.byte	0x01, 0x00, 0x01, 0xfc, 0x01, 0xff, 0x01, 0x3f 
			.byte	0x01, 0x1f, 0x01, 0xfe, 0x01, 0xc3, 0x01, 0xc7 
			.byte	0x01, 0x1f, 0x01, 0xff, 0x01, 0xfc, 0x01, 0xff 
			.byte	0x0a, 0x00, 0x01, 0x82, 0x08, 0x00, 0x01, 0x3f 
			.byte	0x02, 0x00, 0x01, 0xff, 0x01, 0x0f, 0x01, 0x87 
			.byte	0x01, 0xff, 0x01, 0xc7, 0x01, 0x87, 0x01, 0x0f 
			.byte	0x03, 0xff, 0x0a, 0x00, 0x01, 0x82, 0x05, 0x00 
			.byte	0x01, 0x01, 0x02, 0x00, 0x01, 0xc0, 0x02, 0x00 
			.byte	0x01, 0xff, 0x01, 0x03, 0x01, 0xc0, 0x01, 0xff 
			.byte	0x01, 0x87, 0x01, 0x0f, 0x01, 0x8f, 0x03, 0xff 
			.byte	0x01, 0x00, 0x01, 0xc0, 0x08, 0x00, 0x01, 0x82 
			.byte	0x05, 0x00, 0x01, 0x06, 0x05, 0x00, 0x01, 0xff 
			.byte	0x01, 0x00, 0x01, 0xf8, 0x01, 0xff, 0x01, 0x0f 
			.byte	0x01, 0x1f, 0x01, 0x8f, 0x03, 0xff, 0x01, 0x00 
			.byte	0x01, 0xf8, 0x08, 0x00, 0x01, 0x43, 0x05, 0x00 
			.byte	0x01, 0x38, 0x05, 0x00, 0x01, 0x1f, 0x01, 0x00 
			.byte	0x02, 0xff, 0x01, 0x1f, 0x01, 0xfe, 0x01, 0x0f 
			.byte	0x03, 0xff, 0x01, 0x00, 0x01, 0xfe, 0x08, 0x00 
			.byte	0x01, 0xff, 0x02, 0x00, 0x01, 0x80, 0x02, 0x00 
			.byte	0x01, 0xe0, 0x05, 0x00, 0x01, 0x07, 0x01, 0x00 
			.byte	0x02, 0xff, 0x01, 0x3f, 0x01, 0xfc, 0x01, 0x1f 
			.byte	0x03, 0xff, 0x01, 0xc0, 0x01, 0xff, 0x08, 0x00 
			.byte	0x01, 0xff, 0x02, 0x00, 0x01, 0x80, 0x03, 0x00 
			.byte	0x01, 0x0f, 0x04, 0x00, 0x01, 0x01, 0x01, 0x00 
			.byte	0x02, 0xff, 0x01, 0x7f, 0x01, 0xf8, 0x01, 0x1f 
			.byte	0x01, 0xfe, 0x02, 0xff, 0x01, 0xf0, 0x01, 0xff 
			.byte	0x08, 0x00, 0x01, 0xff, 0x01, 0x01, 0x01, 0x00 
			.byte	0x01, 0x80, 0x03, 0x00, 0x01, 0x78, 0x06, 0x00 
			.byte	0x01, 0xff, 0x01, 0x7f, 0x01, 0x3f, 0x01, 0xf8 
			.byte	0x01, 0x3f, 0x01, 0xfc, 0x02, 0xff, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x08, 0x00, 0x01, 0xff, 0x01, 0x03 
			.byte	0x01, 0x00, 0x01, 0xc0, 0x01, 0x03, 0x02, 0x00 
			.byte	0x01, 0xc0, 0x06, 0x00, 0x01, 0xff, 0x02, 0x0f 
			.byte	0x01, 0xfe, 0x01, 0x7f, 0x01, 0xf8, 0x04, 0xff 
			.byte	0x01, 0x00, 0x01, 0xc0, 0x06, 0x00, 0x01, 0xff 
			.byte	0x01, 0x07, 0x01, 0x00, 0x01, 0xc0, 0x01, 0x1c 
			.byte	0x09, 0x00, 0x01, 0xff, 0x01, 0x03, 0x01, 0x81 
			.byte	0x02, 0xff, 0x01, 0xe0, 0x04, 0xff, 0x01, 0x00 
			.byte	0x01, 0xf0, 0x06, 0x00, 0x01, 0xff, 0x01, 0x07 
			.byte	0x01, 0x00, 0x01, 0xc0, 0x01, 0xe0, 0x09, 0x00 
			.byte	0x01, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x02, 0xff 
			.byte	0x01, 0x01, 0x04, 0xff, 0x01, 0x00, 0x01, 0xfe 
			.byte	0x06, 0x00, 0x01, 0xff, 0x01, 0x07, 0x01, 0x00 
			.byte	0x01, 0xc0, 0x01, 0x00, 0x01, 0x0f, 0x08, 0x00 
			.byte	0x01, 0x1f, 0x01, 0x00, 0x01, 0xfe, 0x02, 0xff 
			.byte	0x01, 0x0f, 0x04, 0xff, 0x01, 0xc0, 0x01, 0xff 
			.byte	0x06, 0x00, 0x01, 0xff, 0x01, 0x07, 0x01, 0x00 
			.byte	0x01, 0xc0, 0x01, 0x00, 0x01, 0xf0, 0x08, 0x00 
			.byte	0x01, 0x07, 0x01, 0x00, 0x08, 0xff, 0x01, 0xe0 
			.byte	0x01, 0xff, 0x06, 0x00, 0x01, 0xff, 0x01, 0x03 
			.byte	0x01, 0x0f, 0x01, 0xc0, 0x0a, 0x00, 0x01, 0x01 
			.byte	0x01, 0x00, 0x08, 0xff, 0x01, 0xf8, 0x01, 0xff 
			.byte	0x06, 0x00, 0x01, 0x3f, 0x01, 0x00, 0x01, 0xf0 
			.byte	0x01, 0x3f, 0x0c, 0x00, 0x01, 0xff, 0x01, 0x7f 
			.byte	0x06, 0xff, 0x01, 0xfc, 0x01, 0xff, 0x06, 0x00 
			.byte	0x01, 0x14, 0x02, 0x00, 0x01, 0x08, 0x0c, 0x00 
			.byte	0x01, 0xff, 0x01, 0x0f, 0x06, 0xff, 0x01, 0xfe 
			.byte	0x01, 0xff, 0x06, 0x00, 0x01, 0x14, 0x0f, 0x00 
			.byte	0x01, 0xff, 0x01, 0x03, 0x08, 0xff, 0x06, 0x00 
			.byte	0x01, 0x14, 0x0f, 0x00, 0x01, 0xff, 0x01, 0x00 
			.byte	0x08, 0xff, 0x01, 0x00, 0x01, 0x80, 0x04, 0x00 
			.byte	0x01, 0x14, 0x0f, 0x00, 0x01, 0x3f, 0x01, 0x00 
			.byte	0x08, 0xff, 0x01, 0x00, 0x01, 0x80, 0x04, 0x00 
			.byte	0x01, 0x14, 0x0f, 0x00, 0x01, 0x07, 0x01, 0x00 
			.byte	0x08, 0xff, 0x01, 0x00, 0x01, 0x80, 0x04, 0x00 
			.byte	0x01, 0x12, 0x0f, 0x00, 0x01, 0x01, 0x01, 0x00 
			.byte	0x08, 0xff, 0x01, 0x00, 0x01, 0xc0, 0x04, 0x00 
			.byte	0x01, 0x12, 0x11, 0x00, 0x01, 0xff, 0x01, 0x7f 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xc0, 0x04, 0x00 
			.byte	0x01, 0x12, 0x11, 0x00, 0x01, 0xff, 0x01, 0x1f 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xc0, 0x04, 0x00 
			.byte	0x01, 0x12, 0x11, 0x00, 0x01, 0xff, 0x01, 0x03 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xe0, 0x04, 0x00 
			.byte	0x01, 0x12, 0x11, 0x00, 0x01, 0xff, 0x01, 0x00 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xe0, 0x04, 0x00 
			.byte	0x01, 0x0a, 0x11, 0x00, 0x01, 0x3f, 0x01, 0x00 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xe0, 0x04, 0x00 
			.byte	0x01, 0x0a, 0x11, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x04, 0x00 
			.byte	0x01, 0x0a, 0x11, 0x00, 0x01, 0x01, 0x01, 0x00 
			.byte	0x06, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x04, 0x00 
			.byte	0x01, 0x0a, 0x13, 0x00, 0x01, 0xff, 0x01, 0x7f 
			.byte	0x04, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x04, 0x00 
			.byte	0x01, 0x0a, 0x13, 0x00, 0x01, 0xff, 0x01, 0x1f 
			.byte	0x04, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x04, 0x00 
			.byte	0x01, 0x0a, 0x13, 0x00, 0x01, 0xff, 0x01, 0x07 
			.byte	0x04, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x04, 0x00 
			.byte	0x01, 0x06, 0x13, 0x00, 0x01, 0xff, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0x00, 0x01, 0xf0, 0x04, 0x00 
			.byte	0x01, 0x06, 0x13, 0x00, 0x01, 0x3f, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0x00, 0x01, 0xe0, 0x04, 0x00 
			.byte	0x01, 0x06, 0x13, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0x00, 0x01, 0xe0, 0x04, 0x00 
			.byte	0x01, 0x06, 0x13, 0x00, 0x01, 0x03, 0x01, 0x00 
			.byte	0x04, 0xff, 0x01, 0x00, 0x01, 0xc0, 0x04, 0x00 
			.byte	0x01, 0x06, 0x15, 0x00, 0x01, 0xff, 0x01, 0x7f 
			.byte	0x02, 0xff, 0x01, 0x00, 0x01, 0xc0, 0x1a, 0x00 
			.byte	0x01, 0xff, 0x01, 0x1f, 0x02, 0xff, 0x01, 0x00 
			.byte	0x01, 0x80, 0x1a, 0x00, 0x01, 0xff, 0x01, 0x07 
			.byte	0x02, 0xff, 0x01, 0x00, 0x01, 0x80, 0x1a, 0x00 
			.byte	0x01, 0xff, 0x01, 0x01, 0x02, 0xff, 0x01, 0x00 
			.byte	0x01, 0x80, 0x1a, 0x00, 0x01, 0x3f, 0x01, 0x00 
			.byte	0x02, 0xff, 0x1c, 0x00, 0x01, 0x0f, 0x01, 0x00 
			.byte	0x02, 0xff, 0x1c, 0x00, 0x01, 0x03, 0x01, 0x00 
			.byte	0x01, 0xfe, 0x01, 0xff, 0x1e, 0x00, 0x01, 0xfc 
			.byte	0x01, 0xff, 0x1e, 0x00, 0x01, 0xf8, 0x01, 0x1f 
			.byte	0x1e, 0x00, 0x01, 0xf0, 0x01, 0x03, 0xff, 0x00 
			.byte	0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00 
			.byte	0xff, 0x00

; Frame 2 of logo. This contains only differences, and is compressed.
.global	logo_fr2
logo_fr2:	.byte	0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00 
			.byte	0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00 
			.byte	0xff, 0x00, 0x4d, 0x00, 0x01, 0x0c, 0x1f, 0x00 
			.byte	0x01, 0x14, 0x1f, 0x00, 0x01, 0x14, 0x1f, 0x00 
			.byte	0x01, 0x14, 0x1f, 0x00, 0x01, 0x24, 0x1f, 0x00 
			.byte	0x01, 0x24, 0x1f, 0x00, 0x01, 0x24, 0x1f, 0x00 
			.byte	0x01, 0x24, 0x1f, 0x00, 0x01, 0x42, 0x1f, 0x00 
			.byte	0x01, 0x42, 0x1f, 0x00, 0x01, 0x42, 0x1f, 0x00 
			.byte	0x01, 0x42, 0x1f, 0x00, 0x01, 0x42, 0x1f, 0x00 
			.byte	0x01, 0x42, 0x1f, 0x00, 0x01, 0x42, 0x1f, 0x00 
			.byte	0x01, 0x42, 0x1f, 0x00, 0x01, 0x82, 0x1d, 0x00 
			.byte	0x01, 0x80, 0x01, 0x07, 0x01, 0x82, 0x1d, 0x00 
			.byte	0x01, 0x70, 0x01, 0x04, 0x01, 0x82, 0x1d, 0x00 
			.byte	0x01, 0x0c, 0x01, 0x06, 0x01, 0x82, 0x1d, 0x00 
			.byte	0x02, 0x03, 0x02, 0x80, 0x1c, 0x00, 0x01, 0xc0 
			.byte	0x01, 0x00, 0x01, 0x80, 0x01, 0xc0, 0x1c, 0x00 
			.byte	0x01, 0x20, 0x01, 0x00, 0x01, 0x84, 0x01, 0x30 
			.byte	0x1c, 0x00, 0x01, 0x18, 0x01, 0x00, 0x01, 0x8d 
			.byte	0x01, 0x0c, 0x1c, 0x00, 0x01, 0x06, 0x01, 0x00 
			.byte	0x01, 0x9d, 0x01, 0x06, 0x1c, 0x00, 0x01, 0x01 
			.byte	0x01, 0x00, 0x01, 0x7c, 0x01, 0x01, 0x01, 0x00 
			.byte	0x01, 0x80, 0x1d, 0x00, 0x01, 0xc0, 0x1f, 0x00 
			.byte	0x01, 0x30, 0x01, 0x00, 0x01, 0x40, 0x1d, 0x00 
			.byte	0x01, 0x18, 0x1f, 0x00, 0x01, 0x04, 0x61, 0x00 
			.byte	0x01, 0x20, 0x1f, 0x00, 0x01, 0x18, 0x1f, 0x00 
			.byte	0x01, 0x07, 0x1f, 0x00, 0x01, 0x06, 0x1c, 0x00 
			.byte	0x01, 0x14, 0x01, 0x00, 0x01, 0x70, 0x1d, 0x00 
			.byte	0x01, 0x14, 0x01, 0x00, 0x01, 0x18, 0x01, 0x07 
			.byte	0x1c, 0x00, 0x01, 0x14, 0x01, 0x00, 0x01, 0xe6 
			.byte	0x1d, 0x00, 0x01, 0x14, 0x01, 0x00, 0x01, 0x39 
			.byte	0x02, 0x00, 0x01, 0x80, 0x1a, 0x00, 0x01, 0x14 
			.byte	0x01, 0x00, 0x01, 0x07, 0x02, 0x00, 0x01, 0xc0 
			.byte	0x1a, 0x00, 0x01, 0x12, 0x04, 0x00, 0x01, 0xf0 
			.byte	0x1a, 0x00, 0x01, 0x12, 0x04, 0x00, 0x01, 0x10 
			.byte	0x1a, 0x00, 0x01, 0x12, 0x1f, 0x00, 0x01, 0x12 
			.byte	0x1f, 0x00, 0x01, 0x12, 0x1f, 0x00, 0x01, 0x0a 
			.byte	0x1f, 0x00, 0x01, 0x0a, 0x1f, 0x00, 0x01, 0x0a 
			.byte	0x1f, 0x00, 0x01, 0x0a, 0x1f, 0x00, 0x01, 0x0a 
			.byte	0x1f, 0x00, 0x01, 0x0a, 0x1f, 0x00, 0x01, 0x06 
			.byte	0x1f, 0x00, 0x01, 0x06, 0x1f, 0x00, 0x01, 0x06 
			.byte	0x1f, 0x00, 0x01, 0x06, 0x1f, 0x00, 0x01, 0x06 
			.byte	0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00 
			.byte	0xff, 0x00, 0xff, 0x00, 0xff, 0x00

.end
