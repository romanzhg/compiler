# start of generated code
	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	2
_bool_tag:
	.word	3
_string_tag:
	.word	4
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const16:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const2
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bazz"
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Razz"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"Bar"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"Foo"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const6
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const7
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const7
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const8
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const6
	.ascii	"do nothing"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const9
	.ascii	"./hairyscary.cl"
	.byte	0	
	.align	2
	.word	-1
int_const9:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	15
	.word	-1
int_const8:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const7:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	9
	.word	-1
int_const6:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const5:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const4:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const3:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const2:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
int_const1:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const0:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
bool_const0:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const6
	.word	str_const7
	.word	str_const8
	.word	str_const9
	.word	str_const10
	.word	str_const14
	.word	str_const11
	.word	str_const13
	.word	str_const12
	.word	str_const15
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	Bazz_protObj
	.word	Bazz_init
	.word	Foo_protObj
	.word	Foo_init
	.word	Razz_protObj
	.word	Razz_init
	.word	Bar_protObj
	.word	Bar_init
	.word	Main_protObj
	.word	Main_init
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Bazz_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Bazz.doh
Foo_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh
Razz_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh
Bar_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Main.main
	.word	-1
Main_protObj:
	.word	9
	.word	7
	.word	Main_dispTab
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-1
Bazz_protObj:
	.word	5
	.word	6
	.word	Bazz_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	-1
Razz_protObj:
	.word	7
	.word	10
	.word	Razz_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	0
	.word	int_const2
	.word	-1
Bar_protObj:
	.word	8
	.word	12
	.word	Bar_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	0
	.word	int_const2
	.word	int_const2
	.word	0
	.word	-1
Foo_protObj:
	.word	6
	.word	8
	.word	Foo_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	-1
String_protObj:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const2
	.word	0
	.word	-1
Bool_protObj:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	li	$t1 5
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	sw	$a0 12($s0)
	li	$t1 6
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	sw	$a0 16($s0)
	li	$t1 7
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	sw	$a0 20($s0)
	li	$t1 8
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	sw	$a0 24($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bazz_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
	la	$a0 int_const1
	sw	$a0 12($s0)
	move	$a0 $s0
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label0:
	lw	$t1 0($a0)
	bgt	$t1 8 label2
	blt	$t1 8 label2
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	lw	$a0 -4($fp)
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label1
label2:
	bgt	$t1 8 label3
	blt	$t1 7 label3
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	li	$t1 8
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label1
label3:
	bgt	$t1 8 label4
	blt	$t1 6 label4
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	li	$t1 7
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label1
label4:
	bgt	$t1 8 label5
	blt	$t1 5 label5
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	li	$t1 6
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label1
label5:
	jal	_case_abort
label1:
	sw	$a0 16($s0)
	addiu	$sp $sp 0
	move	$a0 $s0
	bne	$a0 $zero label6
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label6:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 20($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Razz_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Foo_init
	move	$a0 $s0
	bne	$a0 $zero label7
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label7:
	lw	$t1 0($a0)
	bgt	$t1 8 label9
	blt	$t1 8 label9
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	lw	$a0 -4($fp)
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label8
label9:
	bgt	$t1 8 label10
	blt	$t1 7 label10
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	li	$t1 8
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label8
label10:
	jal	_case_abort
label8:
	sw	$a0 32($s0)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	lw	$a0 24($s0)
	bne	$a0 $zero label11
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label11:
	la	$t1 Bazz_protObj
	lw	$t1 8($t1)
	lw	$t1 32($t1)
	jalr		$t1
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	lw	$a0 16($s0)
	bne	$a0 $zero label12
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label12:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	lw	$a0 32($s0)
	bne	$a0 $zero label13
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label13:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	move	$a0 $s0
	bne	$a0 $zero label14
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label14:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	move	$a0 $s0
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label15:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	sw	$a0 36($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bar_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Razz_init
	addiu	$sp $sp 0
	move	$a0 $s0
	bne	$a0 $zero label16
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label16:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$a0 40($s0)
	addiu	$sp $sp 0
	move	$a0 $s0
	bne	$a0 $zero label17
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label17:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 44($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Foo_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Bazz_init
	move	$a0 $s0
	bne	$a0 $zero label18
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label18:
	lw	$t1 0($a0)
	bgt	$t1 8 label20
	blt	$t1 8 label20
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	lw	$a0 -4($fp)
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label19
label20:
	bgt	$t1 8 label21
	blt	$t1 7 label21
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	li	$t1 8
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label19
label21:
	bgt	$t1 8 label22
	blt	$t1 6 label22
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	li	$t1 7
	sll	$t1 $t1 3
	la	$t2 class_objTab
	add	$t1 $t1 $t2
	addiu	$sp $sp -4
	sw	$t1 4($sp)
	lw	$a0 0($t1)
	jal	Object.copy
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t2 4($t1)
	jalr		$t2
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	b	label19
label22:
	jal	_case_abort
label19:
	sw	$a0 24($s0)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	lw	$a0 24($s0)
	bne	$a0 $zero label23
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label23:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	lw	$a0 16($s0)
	bne	$a0 $zero label24
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label24:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	move	$a0 $s0
	bne	$a0 $zero label25
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label25:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	addiu	$sp $sp 0
	move	$a0 $s0
	bne	$a0 $zero label26
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label26:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	sw	$a0 28($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Object_init:
	jr	$ra	
Main.main:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bazz.printh:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$a0 4($sp)
	move	$a0 $s0
	bne	$a0 $zero label27
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label27:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	la	$a0 int_const2
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bazz.doh:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	lw	$a0 12($s0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 int_const1
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	sw	$a0 12($s0)
	lw	$a0 -4($fp)
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Foo.doh:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 Int_protObj
	jal	Object.copy
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	lw	$a0 12($s0)
	addiu	$sp $sp -4
	sw	$a0 4($sp)
	la	$a0 int_const0
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	add	$t1 $t1 $a0
	lw	$a0 4($sp)
	addiu	$sp $sp 4
	sw	$t1 12($a0)
	sw	$a0 12($s0)
	lw	$a0 -4($fp)
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	

# end of generated code
