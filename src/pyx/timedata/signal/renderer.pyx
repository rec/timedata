cdef extern from "<timedata/color/renderer_inl.h>" namespace "timedata::color_list":
    cdef cppclass CRenderer:
        CRenderer(Render3&)
        CRenderer()
        void render(float level, RGBIndexer& input,
                    size_t offset, size_t size, char* out)
        void render(float level, RGBIndexer& input,
                    size_t offset, size_t size, uint64_t out)


cdef class Renderer(_Render3):
    cdef CRenderer renderer
    cdef float level

    def __init__(self, *, level=1.0, **kwds):
        super().__init__(**kwds)
        self.renderer = CRenderer(self.cdata)
        self.level = level

    property level:
        def __get__(self):
            return self.level
        def __set__(self, float x):
            self.level = x

    def render(self, object colors, size_t offset=0, int length=-1,
               object buf=None):
        cdef Indexer indexer = <Indexer> colors.indexer()
        cdef size_t size = len(colors) if length < 0 else length

        buf = buf or bytearray(3 * size)
        if isinstance(buf, bytearray):
            self.renderer.render(
                self.level, indexer.cdata, offset, size, <bytearray> buf)
        else:
            self.renderer.render(
                self.level, indexer.cdata, offset, size, <uint64_t> buf)
        return buf
