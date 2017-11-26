#
# OpenSSL/Makefile
#
LITEOS_CFLAGS += -Wno-error
HIARCH := hi3518e
OSTYPE := HuaweiLite
CROSS_COMPILE = arm-hisiv500-linux-
LITEOSTOPDIR := $(shell pwd)/../../../osdrv/$(HIARCH)v200/opensource/liteos/liteos
include $(LITEOSTOPDIR)/config.mk

ARFLAGS = cr
BUILD = out

LIBOUT = $(BUILD)/openssl
LIBCRYPTO = $(LIBOUT)/lib/libopenssl.a
RM = -rm -rf

LOCAL_INCLUDE := \
	-I . \
    -I ./include \
	-I ./crypto \
	-I ./crypto/asn1 \
	-I ./crypto/evp \
	-I ./crypto/des \
	-I ./crypto/modes \
	-I ./ssl \
	-I $(LITEOSTOPDIR)/lib/cxxstl/gccinclude/sys \
	-I $(LITEOSTOPDIR)/net/lwip_sack/include/lwip \
	-I $(LITEOSTOPDIR)/fs/include/fs \
	-I $(LITEOSTOPDIR)/lib/cxxstl/gccinclude/bits \

SRCSC = $(wildcard crypto/objects/*.c)  $(wildcard crypto/md4/*.c)      $(wildcard crypto/rsa/*.c)\
	    $(wildcard crypto/sha/*.c)      $(wildcard crypto/mdc2/*.c)     $(wildcard crypto/hmac/*.c) \
		$(wildcard crypto/ripemd/*.c)   $(wildcard crypto/whrlpool/*.c) $(wildcard crypto/des/*.c) \
		$(wildcard crypto/aes/*.c)      $(wildcard crypto/rc2/*.c)      $(wildcard crypto/rc4/*.c) \
		$(wildcard crypto/idea/*.c)     $(wildcard crypto/bf/*.c)       $(wildcard crypto/cast/*.c) \
		$(wildcard crypto/camellia/*.c) $(wildcard crypto/modes/*.c)    $(wildcard crypto/seed/*.c)\
		$(wildcard crypto/dsa/*.c)      $(wildcard crypto/ecdsa/*.c)    $(wildcard crypto/dh/*.c) \
        $(wildcard crypto/ecdh/*.c)     $(wildcard crypto/dso/*.c)      $(wildcard crypto/engine/*.c) \
		$(wildcard crypto/buffer/*.c)   $(wildcard crypto/bio/*.c)      $(wildcard crypto/stack/*.c) \
		$(wildcard crypto/lhash/*.c)    $(wildcard crypto/rand/*.c)     $(wildcard crypto/err/*.c) \
		$(wildcard crypto/evp/*.c)      $(wildcard crypto/asn1/*.c)     $(wildcard crypto/pem/*.c) \
		$(wildcard crypto/x509/*.c)     $(wildcard crypto/x509v3/*.c)   $(wildcard crypto/conf/*.c) \
		$(wildcard crypto/txt_db/*.c)   $(wildcard crypto/pkcs7/*.c)    $(wildcard crypto/pkcs12/*.c) \
		$(wildcard crypto/comp/*.c)     $(wildcard crypto/ocsp/*.c)     $(wildcard crypto/ui/*.c) \
	    $(wildcard crypto/krb5/*.c)     $(wildcard crypto/cms/*.c)      $(wildcard crypto/pqueue/*.c) \
	    $(wildcard crypto/ts/*.c)       $(wildcard crypto/srp/*.c)      $(wildcard crypto/cmac/*.c) \
		$(wildcard crypto/bn/*.c)
		
SRCSC += crypto/cryptlib.c crypto/mem.c crypto/mem_clr.c crypto/mem_dbg.c crypto/cversion.c crypto/ex_data.c crypto/cpt_err.c \
	     crypto/ebcdic.c   crypto/uid.c crypto/o_time.c  crypto/o_str.c   crypto/o_dir.c    crypto/o_fips.c  crypto/o_init.c crypto/fips_ers.c \

SRCSC += crypto/md5/md5_dgst.c crypto/md5/md5_one.c

SRCSC += crypto/ec/ec_lib.c       crypto/ec/ecp_smpl.c     crypto/ec/ecp_mont.c     crypto/ec/ecp_nist.c crypto/ec/ec_cvt.c  crypto/ec/ec_mult.c\
	     crypto/ec/ec_err.c       crypto/ec/ec_curve.c     crypto/ec/ec_check.c     crypto/ec/ec_print.c crypto/ec/ec_asn1.c crypto/ec/ec_key.c\
	     crypto/ec/ec2_smpl.c     crypto/ec/ec2_mult.c     crypto/ec/ec_ameth.c     crypto/ec/ec_pmeth.c crypto/ec/eck_prn.c \
	     crypto/ec/ecp_nistp224.c crypto/ec/ecp_nistp256.c crypto/ec/ecp_nistp521.c crypto/ec/ecp_nistputil.c \
	     crypto/ec/ecp_oct.c      crypto/ec/ec2_oct.c      crypto/ec/ec_oct.c
  
SRCSC +=	\
	ssl/s2_meth.c  ssl/s2_srvr.c  ssl/s2_clnt.c  ssl/s2_lib.c   ssl/s2_enc.c   ssl/s2_pkt.c \
	ssl/s3_meth.c  ssl/s3_srvr.c  ssl/s3_clnt.c  ssl/s3_lib.c   ssl/s3_enc.c   ssl/s3_pkt.c \
	ssl/s3_both.c  ssl/s3_cbc.c   ssl/s23_meth.c ssl/s23_srvr.c ssl/s23_clnt.c ssl/s23_lib.c  \
	ssl/s23_pkt.c  ssl/t1_meth.c  ssl/t1_srvr.c  ssl/t1_clnt.c  ssl/t1_lib.c   ssl/t1_enc.c \
	ssl/t1_ext.c   ssl/d1_meth.c  ssl/d1_srvr.c  ssl/d1_clnt.c  ssl/d1_lib.c   ssl/d1_pkt.c \
	ssl/d1_both.c  ssl/d1_srtp.c  ssl/ssl_lib.c  ssl/ssl_err2.c ssl/ssl_cert.c ssl/ssl_sess.c \
	ssl/ssl_ciph.c ssl/ssl_stat.c ssl/ssl_rsa.c  ssl/ssl_asn1.c ssl/ssl_txt.c  ssl/ssl_algs.c \
	ssl/ssl_conf.c ssl/bio_ssl.c  ssl/ssl_err.c  ssl/kssl.c     ssl/t1_reneg.c ssl/tls_srp.c \
	ssl/t1_trce.c  ssl/ssl_utst.c \
		  
OBJSC = $(patsubst %.c,$(LIBOUT)/%.o,$(SRCSC))

all: $(LIBOUT) $(LIBCRYPTO)

$(OBJSC): $(LIBOUT)/%.o : %.c
	@$(CC) $(LITEOS_CFLAGS) $(LOCAL_INCLUDE) $(LITEOS_INCLUDE) -DPEDANTIC -c $< -o $@

$(LIBCRYPTO): $(OBJSC)
	@$(AR) $(ARFLAGS) $@ $(OBJSC)

$(LIBOUT):
	@mkdir -p $(LIBOUT)/crypto          $(LIBOUT)/crypto/objects $(LIBOUT)/crypto/md4      $(LIBOUT)/crypto/rsa    $(LIBOUT)/crypto/md5    $(LIBOUT)/crypto/sha    $(LIBOUT)/crypto/mdc2
	@mkdir -p $(LIBOUT)/crypto/hmac     $(LIBOUT)/crypto/ripemd  $(LIBOUT)/crypto/whrlpool $(LIBOUT)/crypto/des    $(LIBOUT)/crypto/aes    $(LIBOUT)/crypto/ec
	@mkdir -p $(LIBOUT)/crypto/rc2      $(LIBOUT)/crypto/rc4     $(LIBOUT)/crypto/idea     $(LIBOUT)/crypto/bf     $(LIBOUT)/crypto/cast
	@mkdir -p $(LIBOUT)/crypto/camellia $(LIBOUT)/crypto/modes   $(LIBOUT)/crypto/seed     $(LIBOUT)/crypto/dsa    $(LIBOUT)/crypto/ecdsa
	@mkdir -p $(LIBOUT)/crypto/dh       $(LIBOUT)/crypto/ecdh    $(LIBOUT)/crypto/dso      $(LIBOUT)/crypto/engine $(LIBOUT)/crypto/buffer
	@mkdir -p $(LIBOUT)/crypto/bio      $(LIBOUT)/crypto/stack   $(LIBOUT)/crypto/lhash    $(LIBOUT)/crypto/rand   $(LIBOUT)/crypto/err
	@mkdir -p $(LIBOUT)/crypto/evp      $(LIBOUT)/crypto/asn1    $(LIBOUT)/crypto/pem      $(LIBOUT)/crypto/x509   $(LIBOUT)/crypto/x509v3
	@mkdir -p $(LIBOUT)/crypto/conf     $(LIBOUT)/crypto/txt_db  $(LIBOUT)/crypto/pkcs7    $(LIBOUT)/crypto/pkcs12 $(LIBOUT)/crypto/comp
	@mkdir -p $(LIBOUT)/crypto/ocsp     $(LIBOUT)/crypto/ui      $(LIBOUT)/crypto/krb5     $(LIBOUT)/crypto/cms    $(LIBOUT)/crypto/pqueue
	@mkdir -p $(LIBOUT)/crypto/ts       $(LIBOUT)/crypto/srp     $(LIBOUT)/crypto/cmac     $(LIBOUT)/crypto/bn     $(LIBOUT)/ssl            $(LIBOUT)/lib

clean:
	@$(RM) $(LIBOUT) $(LIBCRYPTO) *.bak *~

.PHONY: all clean
