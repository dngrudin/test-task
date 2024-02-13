
#include "MD5.hpp"

MD5::MD5() : mMDCtx(EVP_MD_CTX_new()) {}

MD5::~MD5() { EVP_MD_CTX_free(mMDCtx); }

void MD5::prepare() {
  EVP_MD_CTX_reset(mMDCtx);
  EVP_DigestInit_ex(mMDCtx, EVP_md5(), NULL);
}

void MD5::update(unsigned char *buffer, unsigned int bufferSize) {
  EVP_DigestUpdate(mMDCtx, buffer, bufferSize);
}

void MD5::final(unsigned char *digest) {
  unsigned int digestLen = 0;
  EVP_DigestFinal_ex(mMDCtx, digest, &digestLen);
}

std::size_t MD5::getDigestLenght() { return EVP_MD_size(EVP_md5()); }
