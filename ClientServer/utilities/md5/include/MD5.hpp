#ifndef MD5_HPP
#define MD5_HPP

#include <openssl/evp.h>

class MD5 {
public:
  MD5();
  ~MD5();

  void prepare();
  void update(unsigned char *buffer, unsigned int bufferSize);
  void final(unsigned char *digest);

  static std::size_t getDigestLenght();

private:
  EVP_MD_CTX *mMDCtx;
};

#endif // MD5_HPP