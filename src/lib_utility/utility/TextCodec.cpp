// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TextCodec.h"

#include <QTextCodec>

TextCodec::TextCodec(std::string name) noexcept
    : m_name(std::move(name)),
      m_codec(QTextCodec::codecForName(m_name.c_str())),
      m_decoder(std::make_shared<QTextDecoder>(m_codec)),
      m_encoder(std::make_shared<QTextEncoder>(m_codec)) {}

std::string TextCodec::getName() const { return m_name; }

bool TextCodec::isValid() const { return m_codec != nullptr; }

std::wstring TextCodec::decode(const std::string& unicodeString) const {
  if (m_decoder) {
    return m_decoder->toUnicode(unicodeString.c_str()).toStdWString();
  }
  return QString::fromStdString(unicodeString).toStdWString();
}

std::string TextCodec::encode(const std::wstring& string) const {
  if (m_encoder) {
    return m_encoder->fromUnicode(QString::fromStdWString(string)).toStdString();
  }
  return QString::fromStdWString(string).toStdString();
}
