static unsigned char fonts[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0 ����ʸ�� */
  0x00, 0x00, 0x14, 0x00, 0x22, 0x1c, 0x00, 0x00, /* 1 �д� */
  0x00, 0x3e, 0x6b, 0x7f, 0x5d, 0x63, 0x3e, 0x00, /* 2 �д� */
  0x22, 0x77, 0x7f, 0x7f, 0x3e, 0x1c, 0x08, 0x00, /* 3 �ϡ��� */
  0x08, 0x1c, 0x3e, 0x7f, 0x3e, 0x1c, 0x08, 0x00, /* 4 ������ */
  0x08, 0x1c, 0x1c, 0x77, 0x77, 0x08, 0x1c, 0x00, /* 5 �������С� */
  0x08, 0x1c, 0x3e, 0x7f, 0x3e, 0x08, 0x1c, 0x00, /* 6 ���ڡ��� */
  0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, /* 7 �� */
  0x00, 0x00, 0x3c, 0x24, 0x24, 0x3c, 0x00, 0x00, /* 8 �������� */
  0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, /* 9 �������� */
  0x00, 0x7e, 0x42, 0x5a, 0x5a, 0x42, 0x7e, 0x00, /* 10 ���Żͳ� */
  0x0f, 0x03, 0x05, 0x39, 0x48, 0x48, 0x30, 0x00, /* 11 �� */
  0x1c, 0x22, 0x22, 0x1c, 0x08, 0x3e, 0x08, 0x00, /* 12 �� */
  0x18, 0x1c, 0x16, 0x12, 0x12, 0x70, 0x60, 0x00, /* 13 �� */
  0x18, 0x1e, 0x16, 0x12, 0x62, 0x6e, 0x0c, 0x00, /* 14 ���� */
  0x08, 0x2a, 0x1c, 0x77, 0x1c, 0x2a, 0x08, 0x00, /* 15 ��ȯ�� */
  0x10, 0x18, 0x1c, 0x1e, 0x1c, 0x18, 0x10, 0x00, /* 16 �������� */
  0x04, 0x0c, 0x1c, 0x3c, 0x1c, 0x0c, 0x04, 0x00, /* 17 �������� */
  0x08, 0x1c, 0x3e, 0x08, 0x3e, 0x1c, 0x08, 0x00, /* 18 �岼��� */
  0x36, 0x36, 0x36, 0x36, 0x36, 0x00, 0x36, 0x00, /* 19 !! */
  0x00, 0x00, 0x02, 0x06, 0x2c, 0x38, 0x10, 0x00, /* 20 �����å� */
  0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00, /* 21 �������� */
  0x00, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, /* 22 ���� */
  0x08, 0x1c, 0x3e, 0x08, 0x3e, 0x1c, 0x3e, 0x00, /* 23 ����� */
  0x08, 0x1c, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x00, /* 24 �� */
  0x08, 0x08, 0x08, 0x08, 0x3e, 0x1c, 0x08, 0x00, /* 25 �� */
  0x00, 0x04, 0x06, 0x7f, 0x06, 0x04, 0x00, 0x00, /* 26 �� */
  0x00, 0x10, 0x30, 0x7f, 0x30, 0x10, 0x00, 0x00, /* 27 �� */
  0x3c, 0x42, 0x9d, 0xa1, 0xa1, 0x9d, 0x42, 0x3c, /* 28 (C) */
  0x00, 0x14, 0x36, 0x7f, 0x36, 0x14, 0x00, 0x00, /* 29 ���� */
  0x00, 0x08, 0x1c, 0x3e, 0x7f, 0x00, 0x00, 0x00, /* 30 ������� */
  0x00, 0x00, 0x7f, 0x3e, 0x1c, 0x08, 0x00, 0x00, /* 31 �������� */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 32 ���� */
  0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00, /* 33 ! */
  0x36, 0x36, 0x12, 0x24, 0x00, 0x00, 0x00, 0x00, /* 34 " */
  0x14, 0x14, 0x7f, 0x14, 0x7f, 0x14, 0x14, 0x00, /* 35 # */
  0x08, 0x3e, 0x68, 0x3e, 0x0b, 0x3e, 0x08, 0x00, /* 36 $ */
  0x21, 0x52, 0x24, 0x08, 0x12, 0x25, 0x42, 0x00, /* 37 % */
  0x18, 0x24, 0x24, 0x39, 0x4e, 0x44, 0x3b, 0x00, /* 38 & */
  0x0c, 0x0c, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, /* 39 ' */
  0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04, 0x00, /* 40 ( */
  0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x00, /* 41 ) */
  0x00, 0x08, 0x2a, 0x1c, 0x2a, 0x08, 0x00, 0x00, /* 42 * */
  0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 0x00, /* 43 + */
  0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x20, 0x40, /* 44 , */
  0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, /* 45 - */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, /* 46 . */
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, /* 47 / */
  0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00, /* 48 0 */
  0x0c, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, /* 49 1 */
  0x3c, 0x66, 0x06, 0x0c, 0x18, 0x30, 0x7e, 0x00, /* 50 2 */
  0x3c, 0x66, 0x06, 0x3c, 0x06, 0x66, 0x3c, 0x00, /* 51 3 */
  0x0e, 0x1e, 0x36, 0x66, 0x66, 0x7f, 0x06, 0x00, /* 52 4 */
  0x7e, 0x60, 0x60, 0x7c, 0x06, 0x66, 0x3c, 0x00, /* 53 5 */
  0x3c, 0x66, 0x60, 0x7c, 0x66, 0x66, 0x3c, 0x00, /* 54 6 */
  0x7e, 0x66, 0x06, 0x0c, 0x18, 0x18, 0x18, 0x00, /* 55 7 */
  0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x3c, 0x00, /* 56 8 */
  0x3c, 0x66, 0x66, 0x3e, 0x06, 0x66, 0x3c, 0x00, /* 57 9 */
  0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, /* 58 : */
  0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x08, 0x10, /* 59 ; */
  0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00, /* 60 < */
  0x00, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x00, 0x00, /* 61 = */
  0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00, /* 62 > */
  0x3c, 0x66, 0x66, 0x0c, 0x18, 0x00, 0x18, 0x00, /* 63 ? */
  0x3e, 0x45, 0x5d, 0x55, 0x5f, 0x40, 0x3e, 0x00, /* 64 @ */
  0x1c, 0x36, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x00, /* 65 A */
  0x7e, 0x63, 0x63, 0x7e, 0x63, 0x63, 0x7e, 0x00, /* 66 B */
  0x3e, 0x63, 0x60, 0x60, 0x60, 0x63, 0x3e, 0x00, /* 67 C */
  0x7c, 0x66, 0x63, 0x63, 0x63, 0x66, 0x7c, 0x00, /* 68 D */
  0x7e, 0x60, 0x60, 0x7c, 0x60, 0x60, 0x7e, 0x00, /* 69 E */
  0x7e, 0x60, 0x60, 0x7c, 0x60, 0x60, 0x60, 0x00, /* 70 F */
  0x3e, 0x63, 0x60, 0x67, 0x63, 0x63, 0x3e, 0x00, /* 71 G */
  0x63, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x63, 0x00, /* 72 H */
  0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, /* 73 I */
  0x0f, 0x03, 0x03, 0x63, 0x63, 0x63, 0x3e, 0x00, /* 74 J */
  0x63, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0x63, 0x00, /* 75 K */
  0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x00, /* 76 L */
  0x63, 0x77, 0x7f, 0x6b, 0x63, 0x63, 0x63, 0x00, /* 77 M */
  0x63, 0x73, 0x7b, 0x6f, 0x67, 0x63, 0x63, 0x00, /* 78 N */
  0x3e, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, /* 79 O */
  0x7e, 0x63, 0x63, 0x7e, 0x60, 0x60, 0x60, 0x00, /* 80 P */
  0x3e, 0x63, 0x63, 0x6b, 0x6f, 0x67, 0x3e, 0x00, /* 81 Q */
  0x7e, 0x63, 0x63, 0x7e, 0x6c, 0x66, 0x63, 0x00, /* 82 R */
  0x3e, 0x63, 0x60, 0x3e, 0x03, 0x63, 0x3e, 0x00, /* 83 S */
  0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, /* 84 T */
  0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, /* 85 U */
  0x63, 0x63, 0x63, 0x36, 0x36, 0x1c, 0x08, 0x00, /* 86 V */
  0x63, 0x6b, 0x6b, 0x6b, 0x7f, 0x36, 0x22, 0x00, /* 87 W */
  0x63, 0x63, 0x36, 0x1c, 0x36, 0x63, 0x63, 0x00, /* 88 X */
  0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x00, /* 89 Y */
  0x7f, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0x00, /* 90 Z */
  0x1c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1c, 0x00, /* 91 [ */
  0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, /* 92 \ */
  0x1c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1c, 0x00, /* 93 ] */
  0x08, 0x1c, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, /* 94 ^ */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, /* 95 _ */
  0x18, 0x18, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, /* 96 ` */
  0x00, 0x00, 0x3e, 0x66, 0x66, 0x66, 0x3f, 0x00, /* 97 a */
  0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x7c, 0x00, /* 98 b */
  0x00, 0x00, 0x3c, 0x66, 0x60, 0x66, 0x3c, 0x00, /* 99 c */
  0x06, 0x06, 0x3e, 0x66, 0x66, 0x66, 0x3e, 0x00, /* 100 d */
  0x00, 0x00, 0x3c, 0x66, 0x7e, 0x60, 0x3c, 0x00, /* 101 e */
  0x1c, 0x32, 0x30, 0x7c, 0x30, 0x30, 0x30, 0x00, /* 102 f */
  0x00, 0x00, 0x3e, 0x66, 0x66, 0x1e, 0x66, 0x3c, /* 103 g */
  0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x00, /* 104 h */
  0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, /* 105 i */
  0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3c, /* 106 j */
  0x60, 0x60, 0x66, 0x6c, 0x70, 0x6c, 0x66, 0x00, /* 107 k */
  0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, /* 108 l */
  0x00, 0x00, 0x76, 0x6b, 0x6b, 0x6b, 0x6b, 0x00, /* 109 m */
  0x00, 0x00, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x00, /* 110 n */
  0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x3c, 0x00, /* 111 o */
  0x00, 0x00, 0x7c, 0x66, 0x66, 0x7c, 0x60, 0x60, /* 112 p */
  0x00, 0x00, 0x3e, 0x66, 0x66, 0x1e, 0x06, 0x06, /* 113 q */
  0x00, 0x00, 0x6e, 0x70, 0x60, 0x60, 0x60, 0x00, /* 114 r */
  0x00, 0x00, 0x3e, 0x70, 0x3c, 0x0e, 0x7c, 0x00, /* 115 s */
  0x18, 0x18, 0x3e, 0x18, 0x18, 0x18, 0x0e, 0x00, /* 116 t */
  0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3f, 0x00, /* 117 u */
  0x00, 0x00, 0x66, 0x66, 0x24, 0x3c, 0x18, 0x00, /* 118 v */
  0x00, 0x00, 0x63, 0x6b, 0x2a, 0x3e, 0x14, 0x00, /* 119 w */
  0x00, 0x00, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0x00, /* 120 x */
  0x00, 0x00, 0x66, 0x66, 0x3c, 0x18, 0x30, 0x60, /* 121 y */
  0x00, 0x00, 0x7e, 0x0c, 0x18, 0x30, 0x7e, 0x00, /* 122 z */
  0x0c, 0x18, 0x18, 0x30, 0x18, 0x18, 0x0c, 0x00, /* 123 { */
  0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00, /* 124 | */
  0x18, 0x0c, 0x0c, 0x06, 0x0c, 0x0c, 0x18, 0x00, /* 125 } */
  0x32, 0x3c, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, /* 126 ~ */
  0x08, 0x08, 0x14, 0x14, 0x22, 0x22, 0x3e, 0x00  /* 127 �� */
};
