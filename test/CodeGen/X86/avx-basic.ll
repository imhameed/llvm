; RUN: llc < %s -mtriple=x86_64-apple-darwin -mcpu=corei7-avx -mattr=+avx | FileCheck %s

@x = common global <8 x float> zeroinitializer, align 32
@y = common global <4 x double> zeroinitializer, align 32
@z = common global <4 x float> zeroinitializer, align 16

define void @zero128() nounwind ssp {
entry:
  ; CHECK: vxorps
  ; CHECK: vmovaps
  store <4 x float> zeroinitializer, <4 x float>* @z, align 16
  ret void
}

define void @zero256() nounwind ssp {
entry:
  ; CHECK: vxorps
  ; CHECK: vmovaps
  ; CHECK: vmovaps
  store <8 x float> zeroinitializer, <8 x float>* @x, align 32
  store <4 x double> zeroinitializer, <4 x double>* @y, align 32
  ret void
}

; CHECK: vpcmpeqd
; CHECK: vinsertf128 $1
define void @ones([0 x float]* nocapture %RET, [0 x float]* nocapture %aFOO) nounwind {
allocas:
  %ptr2vec615 = bitcast [0 x float]* %RET to <8 x float>*
  store <8 x float> <float 0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float
0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float
0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000>, <8 x
float>* %ptr2vec615, align 32
  ret void
}

; CHECK: vpcmpeqd
; CHECK: vinsertf128 $1
define void @ones2([0 x i32]* nocapture %RET, [0 x i32]* nocapture %aFOO) nounwind {
allocas:
  %ptr2vec615 = bitcast [0 x i32]* %RET to <8 x i32>*
  store <8 x i32> <i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1>, <8 x i32>* %ptr2vec615, align 32
  ret void
}

;;; Just make sure this doesn't crash
; CHECK: _ISelCrash
define <4 x i64> @ISelCrash(<4 x i64> %a) nounwind uwtable readnone ssp {
entry:
  %shuffle = shufflevector <4 x i64> %a, <4 x i64> undef, <4 x i32> <i32 2, i32 3, i32 4, i32 4>
  ret <4 x i64> %shuffle
}

;;;
;;; Check that some 256-bit vectors are xformed into 128 ops
; CHECK: _A
; CHECK: vshufpd $1
; CHECK-NEXT: vextractf128 $1
; CHECK-NEXT: vshufpd $1
; CHECK-NEXT: vinsertf128 $1
define <4 x i64> @A(<4 x i64> %a, <4 x i64> %b) nounwind uwtable readnone ssp {
entry:
  %shuffle = shufflevector <4 x i64> %a, <4 x i64> %b, <4 x i32> <i32 1, i32 0, i32 7, i32 6>
  ret <4 x i64> %shuffle
}

; CHECK: vpunpckhqdq
; CHECK-NEXT: vextractf128  $1
; CHECK-NEXT: movlhps
; CHECK-NEXT: vinsertf128 $1
define <4 x i64> @B(<4 x i64> %a, <4 x i64> %b) nounwind uwtable readnone ssp {
entry:
  %shuffle = shufflevector <4 x i64> %a, <4 x i64> %b, <4 x i32> <i32 1, i32 undef, i32 undef, i32 6>
  ret <4 x i64> %shuffle
}

; CHECK: movlhps
; CHECK-NEXT: vextractf128  $1
; CHECK-NEXT: movlhps
; CHECK-NEXT: vinsertf128 $1
define <4 x i64> @C(<4 x i64> %a, <4 x i64> %b) nounwind uwtable readnone ssp {
entry:
  %shuffle = shufflevector <4 x i64> %a, <4 x i64> %b, <4 x i32> <i32 undef, i32 0, i32 undef, i32 6>
  ret <4 x i64> %shuffle
}

; CHECK: vpshufd $-96
; CHECK: vpshufd $-6
; CHECK: vinsertf128 $1
define <8 x i32> @D(<8 x i32> %a, <8 x i32> %b) nounwind uwtable readnone ssp {
entry:
  %shuffle = shufflevector <8 x i32> %a, <8 x i32> %b, <8 x i32> <i32 0, i32 0, i32 2, i32 2, i32 10, i32 10, i32 11, i32 11>
  ret <8 x i32> %shuffle
}

