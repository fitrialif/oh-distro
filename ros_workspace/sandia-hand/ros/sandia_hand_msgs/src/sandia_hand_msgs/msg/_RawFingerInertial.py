"""autogenerated by genpy from sandia_hand_msgs/RawFingerInertial.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class RawFingerInertial(genpy.Message):
  _md5sum = "47495f9d3649f45640a29f32e4801b17"
  _type = "sandia_hand_msgs/RawFingerInertial"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """uint16[3] mm_accel
uint16[3] pp_accel
uint16[3] dp_accel
uint16[3] mm_mag
uint16[3] pp_mag
uint16[3] dp_mag

"""
  __slots__ = ['mm_accel','pp_accel','dp_accel','mm_mag','pp_mag','dp_mag']
  _slot_types = ['uint16[3]','uint16[3]','uint16[3]','uint16[3]','uint16[3]','uint16[3]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       mm_accel,pp_accel,dp_accel,mm_mag,pp_mag,dp_mag

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(RawFingerInertial, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.mm_accel is None:
        self.mm_accel = [0,0,0]
      if self.pp_accel is None:
        self.pp_accel = [0,0,0]
      if self.dp_accel is None:
        self.dp_accel = [0,0,0]
      if self.mm_mag is None:
        self.mm_mag = [0,0,0]
      if self.pp_mag is None:
        self.pp_mag = [0,0,0]
      if self.dp_mag is None:
        self.dp_mag = [0,0,0]
    else:
      self.mm_accel = [0,0,0]
      self.pp_accel = [0,0,0]
      self.dp_accel = [0,0,0]
      self.mm_mag = [0,0,0]
      self.pp_mag = [0,0,0]
      self.dp_mag = [0,0,0]

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      buff.write(_struct_3H.pack(*self.mm_accel))
      buff.write(_struct_3H.pack(*self.pp_accel))
      buff.write(_struct_3H.pack(*self.dp_accel))
      buff.write(_struct_3H.pack(*self.mm_mag))
      buff.write(_struct_3H.pack(*self.pp_mag))
      buff.write(_struct_3H.pack(*self.dp_mag))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 6
      self.mm_accel = _struct_3H.unpack(str[start:end])
      start = end
      end += 6
      self.pp_accel = _struct_3H.unpack(str[start:end])
      start = end
      end += 6
      self.dp_accel = _struct_3H.unpack(str[start:end])
      start = end
      end += 6
      self.mm_mag = _struct_3H.unpack(str[start:end])
      start = end
      end += 6
      self.pp_mag = _struct_3H.unpack(str[start:end])
      start = end
      end += 6
      self.dp_mag = _struct_3H.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      buff.write(self.mm_accel.tostring())
      buff.write(self.pp_accel.tostring())
      buff.write(self.dp_accel.tostring())
      buff.write(self.mm_mag.tostring())
      buff.write(self.pp_mag.tostring())
      buff.write(self.dp_mag.tostring())
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      start = end
      end += 6
      self.mm_accel = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 6
      self.pp_accel = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 6
      self.dp_accel = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 6
      self.mm_mag = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 6
      self.pp_mag = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 6
      self.dp_mag = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3H = struct.Struct("<3H")
