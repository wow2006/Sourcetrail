#pragma once

#include <memory>
#include <string>

class QTextCodec;
class QTextDecoder;
class QTextEncoder;

class TextCodec final {
 public:
  /**
   * @brief Create Qt decoder/encoder
   *
   * @note pass QTextCodec in the fucture
   *
   * @param name The supported encoder
   */
  explicit TextCodec(std::string name) noexcept;

  [[nodiscard]] std::string getName() const;
  [[nodiscard]] bool isValid() const;

  [[nodiscard]] std::wstring decode(const std::string& unicodeString) const;

  [[nodiscard]] std::string encode(const std::wstring& string) const;

 private:
  const std::string m_name;
  QTextCodec* m_codec;
  std::shared_ptr<QTextDecoder> m_decoder;
  std::shared_ptr<QTextEncoder> m_encoder;
};
