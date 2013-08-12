"""autogenerated by genpy from sandia_hand_msgs/RawMoboState.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class RawMoboState(genpy.Message):
  _md5sum = "4e7e33569ea3b39428acbd57e6ef85b5"
  _type = "sandia_hand_msgs/RawMoboState"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """uint32 mobo_time
float32[4] finger_currents
float32[3] logic_currents
uint16[3] mobo_temp
uint8 mobo_max_effort

"""
  __slots__ = ['mobo_time','finger_currents','logic_currents','mobo_temp','mobo_max_effort']
  _slot_types = ['uint32','float32[4]','float32[3]','uint16[3]','uint8']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       mobo_time,finger_currents,logic_currents,mobo_temp,mobo_max_effort

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(RawMoboState, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.mobo_time is None:
        self.mobo_time = 0
      if self.finger_currents is None:
        self.finger_currents = [0.,0.,0.,0.]
      if self.logic_currents is None:
        self.logic_currents = [0.,0.,0.]
      if self.mobo_temp is None:
        self.mobo_temp = [0,0,0]
      if self.mobo_max_effort is None:
        self.mobo_max_effort = 0
    else:
      self.mobo_time = 0
      self.finger_currents = [0.,0.,0.,0.]
      self.logic_currents = [0.,0.,0.]
      self.mobo_temp = [0,0,0]
      self.mobo_max_effort = 0

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
      buff.write(_struct_I.pack(self.mobo_time))
      buff.write(_struct_4f.pack(*self.finger_currents))
      buff.write(_struct_3f.pack(*self.logic_currents))
      buff.write(_struct_3H.pack(*self.mobo_temp))
      buff.write(_struct_B.pack(self.mobo_max_effort))
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
      end += 4
      (self.mobo_time,) = _struct_I.unpack(str[start:end])
      start = end
      end += 16
      self.finger_currents = _struct_4f.unpack(str[start:end])
      start = end
      end += 12
      self.logic_currents = _struct_3f.unpack(str[start:end])
      start = end
      end += 6
      self.mobo_temp = _struct_3H.unpack(str[start:end])
      start = end
      end += 1
      (self.mobo_max_effort,) = _struct_B.unpack(str[start:end])
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
      buff.write(_struct_I.pack(self.mobo_time))
      buff.write(self.finger_currents.tostring())
      buff.write(self.logic_currents.tostring())
      buff.write(self.mobo_temp.tostring())
      buff.write(_struct_B.pack(self.mobo_max_effort))
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
      end += 4
      (self.mobo_time,) = _struct_I.unpack(str[start:end])
      start = end
      end += 16
      self.finger_currents = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=4)
      start = end
      end += 12
      self.logic_currents = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=3)
      start = end
      end += 6
      self.mobo_temp = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 1
      (self.mobo_max_effort,) = _struct_B.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_4f = struct.Struct("<4f")
_struct_B = struct.Struct("<B")
_struct_3H = struct.Struct("<3H")
_struct_3f = struct.Struct("<3f")
