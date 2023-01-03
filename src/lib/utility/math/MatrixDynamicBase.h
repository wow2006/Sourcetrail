#pragma once

/**
 * @brief Matrix of variable size, needed for spectral graph layouting
 * @note Use MatrixBase whenever possible because it's more efficient (e.g. it doesn't use stl
 * containers)
 */
template <class T>
class MatrixDynamicBase {
public:
  MatrixDynamicBase();
  MatrixDynamicBase(uint32_t numColumns, uint32_t numRows);
  MatrixDynamicBase(const std::vector<std::vector<T>>& values);
  ~MatrixDynamicBase();

  T getValue(uint32_t columnIndex, uint32_t rowIndex) const;
  void setValue(uint32_t columnIndex, uint32_t rowIndex, const T& value);

  [[nodiscard]] uint32_t getColumnsCount() const;
  [[nodiscard]] uint32_t getRowsCount() const;

  [[nodiscard]] std::string toString() const;

private:
  void initializeValues(uint32_t numColumns, uint32_t numRows);

  std::vector<std::vector<T>> m_values;
};

template <class T>
MatrixDynamicBase<T>::MatrixDynamicBase() = default;

template <class T>
MatrixDynamicBase<T>::MatrixDynamicBase(uint32_t numColumns, uint32_t numRows) {
  initializeValues(numColumns, numRows);
}

template <class T>
MatrixDynamicBase<T>::MatrixDynamicBase(const std::vector<std::vector<T>>& values)
    : m_values(values) {}

template <class T>
MatrixDynamicBase<T>::~MatrixDynamicBase() = default;

template <class T>
T MatrixDynamicBase<T>::getValue(uint32_t columnIndex, uint32_t rowIndex) const {
  return m_values[columnIndex][rowIndex];
}

template <class T>
void MatrixDynamicBase<T>::setValue(uint32_t columnIndex,
                                    uint32_t rowIndex,
                                    const T& value) {
  m_values[columnIndex][rowIndex] = value;
}

template <class T>
uint32_t MatrixDynamicBase<T>::getColumnsCount() const {
  return static_cast<uint32_t>(m_values.size());
}

template <class T>
uint32_t MatrixDynamicBase<T>::getRowsCount() const {
  if(m_values.size() > 0) {
    return static_cast<uint32_t>(m_values[0].size());
  }

  return 0;
}

template <class T>
std::string MatrixDynamicBase<T>::toString() const {
  std::stringstream result;

  result << "\n";

  uint32_t rowCount = getRowsCount();
  uint32_t columnCount = getColumnsCount();

  for(uint32_t j = 0; j < rowCount; j++) {
    for(uint32_t i = 0; i < columnCount; i++) {
      if(i > 0) {
        result << ", ";
      }

      result << m_values[i][j];
    }

    result << "\n";
  }

  return result.str();
}

template <class T>
void MatrixDynamicBase<T>::initializeValues(uint32_t numColumns,
                                            uint32_t numRows) {
  for(uint32_t x = 0; x < numColumns; x++) {
    std::vector<T> row;
    for(uint32_t y = 0; y < numRows; y++) {
      row.push_back(0);
    }
    m_values.push_back(row);
  }
}

template <class T>
std::ostream& operator<<(std::ostream& ostream, const MatrixDynamicBase<T>& matrix) {
  ostream << matrix.toString();

  return ostream;
}