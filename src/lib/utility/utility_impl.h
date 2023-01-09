template <typename T>
std::vector<std::vector<T>> utility::splitToEquallySizedParts(const std::vector<T>& values,
                                                              size_t desiredPartCount) {
  const size_t partCount = std::max<size_t>(1, std::min(desiredPartCount, values.size()));

  std::vector<std::vector<T>> parts(partCount);

  size_t i = 0;
  for(const T& value : values) {
    parts[i % partCount].emplace_back(value);
    ++i;
  }

  return parts;
}

template <typename T>
std::vector<T> utility::concat(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> r;
  r.reserve(a.size() + b.size());
  append(r, a);
  append(r, b);
  return r;
}

template <typename T>
std::set<T> utility::concat(const std::set<T>& a, const std::set<T>& b) {
  std::set<T> r;
  append(r, a);
  append(r, b);
  return r;
}

template <typename T>
std::vector<T> utility::concat(const std::vector<T>& a, const T& b) {
  std::vector<T> r = a;
  r.emplace_back(b);
  return r;
}

template <typename T>
std::set<T> utility::concat(const std::set<T>& a, const T& b) {
  std::set<T> r = a;
  r.emplace(b);
  return r;
}

template <typename T>
void utility::append(std::vector<T>& a, const std::vector<T>& b) {
  a.insert(a.end(), b.begin(), b.end());
}

template <typename T>
void utility::append(std::set<T>& a, const std::set<T>& b) {
  a.insert(b.begin(), b.end());
}

template <typename T>
void utility::append(std::unordered_set<T>& a, const std::unordered_set<T>& b) {
  a.insert(b.begin(), b.end());
}

template <typename T>
std::vector<T> utility::unique(const std::vector<T>& a) {
  std::map<T, size_t> unique;

  size_t i = 0;
  for(const T& t: a) {
    if(unique.emplace(t, i).second) {
      i++;
    }
  }

  std::vector<T> r(i, T());
  for(const std::pair<T, size_t>& p: unique) {
    r[p.second] = p.first;
  }

  return r;
}

template <typename T>
std::vector<T> utility::toVector(const std::deque<T>& d) {
  std::vector<T> v;
  v.reserve(d.size());
  v.insert(v.begin(), d.begin(), d.end());
  return v;
}

template <typename T>
std::vector<T> utility::toVector(const std::set<T>& d) {
  std::vector<T> v;
  v.reserve(d.size());
  v.insert(v.begin(), d.begin(), d.end());
  return v;
}

template <typename T>
std::vector<T> utility::toVector(const std::list<T>& d) {
  std::vector<T> v;
  v.reserve(d.size());
  v.insert(v.begin(), d.begin(), d.end());
  return v;
}

template <typename T>
std::set<T> utility::toSet(const std::vector<T>& v) {
  return std::set<T>(v.begin(), v.end());
}

template <typename T>
void utility::fillVectorWithElements(std::vector<T>& v, const T& arg) {
  v.emplace_back(arg);
}

template <typename T, typename... Args>
void utility::fillVectorWithElements(std::vector<T>& v, const T& arg, const Args&... args) {
  fillVectorWithElements<T>(v, arg);
  fillVectorWithElements<T>(v, args...);
}

template <typename T, typename... Args>
std::vector<T> utility::createVectorFromElements(const Args&... args) {
  std::vector<T> v;
  fillVectorWithElements<T>(v, args...);
  return v;
}

template <typename SourceType, typename TargetType>
std::vector<TargetType> utility::convert(const std::vector<SourceType>& sourceContainer,
                                         std::function<TargetType(const SourceType&)> conversion) {
  std::vector<TargetType> targetContainer;
  targetContainer.reserve(sourceContainer.size());
  for(const SourceType& sourceElement: sourceContainer) {
    targetContainer.emplace_back(conversion(sourceElement));
  }
  return targetContainer;
}

template <typename SourceType, typename TargetType>
std::vector<TargetType> utility::convert(const std::vector<SourceType>& sourceContainer) {
  std::vector<TargetType> targetContainer;
  targetContainer.reserve(sourceContainer.size());
  for(const SourceType& sourceElement: sourceContainer) {
    targetContainer.emplace_back(TargetType(sourceElement));
  }
  return targetContainer;
}

template <typename SourceType, typename TargetType>
std::set<TargetType> utility::convert(const std::set<SourceType>& sourceContainer,
                                      std::function<TargetType(const SourceType&)> conversion) {
  std::set<TargetType> targetContainer;
  for(const SourceType& sourceElement: sourceContainer) {
    targetContainer.insert(conversion(sourceElement));
  }
  return targetContainer;
}

template <typename SourceType, typename TargetType>
std::set<TargetType> utility::convert(const std::set<SourceType>& sourceContainer) {
  std::set<TargetType> targetContainer;
  for(const SourceType& sourceElement: sourceContainer) {
    targetContainer.insert(TargetType(sourceElement));
  }
  return targetContainer;
}

template <typename T>
std::vector<std::string> utility::toStrings(const std::vector<T>& d) {
  return convert<T, std::string>(d, [](T t) { return std::to_string(t); });
}

template <>
inline std::vector<std::string> utility::toStrings<utility::file::FilePath>(const std::vector<utility::file::FilePath>& d) {
  return convert<utility::file::FilePath, std::string>(
      d, [](const utility::file::FilePath& fp) { return utility::encodeToUtf8(fp.wstr()); });
}

template <typename T>
std::vector<std::wstring> utility::toWStrings(const std::vector<T>& d) {
  return convert(d, [](T t) { return std::to_wstring(t); });
}

template <>
inline std::vector<std::wstring> utility::toWStrings<utility::file::FilePath>(const std::vector<utility::file::FilePath>& d) {
  return convert<utility::file::FilePath, std::wstring>(d, [](const utility::file::FilePath& fp) { return fp.wstr(); });
}
