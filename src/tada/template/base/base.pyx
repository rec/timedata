### comment
"""This is template code common to both Samples and Lists."""

### declare
import cython
from numbers import Number

cdef extern from "<$include_file>" namespace "$namespace":
    cdef cppclass $class_cpp:
         $class_cpp()
         $class_cpp($value_type, $value_type, $value_type)
         $value_type& operator[](size_t)

    string $to_string($class_cpp&)
    bool cmpToRichcmp($value_type cmp, int richcmp)

### define

cdef class $class_py:
    """$class_documentation"""
    cdef $class_cpp cdata

    @property
    def begin($class_py self):
        """Return the lowest in-band value for this class."""
        return $begin

    @property
    def range($class_py self):
        """Return the range from begin() to the highest in-band value."""
        return $range

    cpdef $class_py copy($class_py self):
        """Return a shallow copy of self."""
        cdef $class_py s = $class_py()
        s.cdata = self.cdata
        return s

    def __repr__($class_py self):
        return '$class_py(%s)' % str(self)

    def __str__($class_py self):
        return $to_string(self.cdata).decode('ascii')

    def __richcmp__($class_py self, $class_py other, int rcmp):
        return cmpToRichcmp($compare(self.cdata, other.cdata), rcmp)