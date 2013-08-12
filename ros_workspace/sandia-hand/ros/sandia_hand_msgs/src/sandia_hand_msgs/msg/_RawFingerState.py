"""autogenerated by genpy from sandia_hand_msgs/RawFingerState.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class RawFingerState(genpy.Message):
  _md5sum = "a2c29ce00f185a2ceab39770dc9bc042"
  _type = "sandia_hand_msgs/RawFingerState"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """uint32 fmcb_time
uint32 pp_time
uint32 dp_time
uint16[6]  pp_tactile
uint16[12] dp_tactile
uint32 pp_strain
int16[3] mm_accel
int16[3] pp_accel
int16[3] dp_accel
uint16[3] mm_mag
uint16[3] pp_mag
uint16[3] dp_mag
uint16[4] pp_temp
uint16[4] dp_temp
uint16[3] fmcb_temp
uint16 fmcb_voltage
uint16 fmcb_pb_current
int32[3] hall_tgt
int32[3] hall_pos
int16[3] fmcb_effort

"""
  __slots__ = ['fmcb_time','pp_time','dp_time','pp_tactile','dp_tactile','pp_strain','mm_accel','pp_accel','dp_accel','mm_mag','pp_mag','dp_mag','pp_temp','dp_temp','fmcb_temp','fmcb_voltage','fmcb_pb_current','hall_tgt','hall_pos','fmcb_effort']
  _slot_types = ['uint32','uint32','uint32','uint16[6]','uint16[12]','uint32','int16[3]','int16[3]','int16[3]','uint16[3]','uint16[3]','uint16[3]','uint16[4]','uint16[4]','uint16[3]','uint16','uint16','int32[3]','int32[3]','int16[3]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       fmcb_time,pp_time,dp_time,pp_tactile,dp_tactile,pp_strain,mm_accel,pp_accel,dp_accel,mm_mag,pp_mag,dp_mag,pp_temp,dp_temp,fmcb_temp,fmcb_voltage,fmcb_pb_current,hall_tgt,hall_pos,fmcb_effort

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(RawFingerState, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.fmcb_time is None:
        self.fmcb_time = 0
      if self.pp_time is None:
        self.pp_time = 0
      if self.dp_time is None:
        self.dp_time = 0
      if self.pp_tactile is None:
        self.pp_tactile = [0,0,0,0,0,0]
      if self.dp_tactile is None:
        self.dp_tactile = [0,0,0,0,0,0,0,0,0,0,0,0]
      if self.pp_strain is None:
        self.pp_strain = 0
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
      if self.pp_temp is None:
        self.pp_temp = [0,0,0,0]
      if self.dp_temp is None:
        self.dp_temp = [0,0,0,0]
      if self.fmcb_temp is None:
        self.fmcb_temp = [0,0,0]
      if self.fmcb_voltage is None:
        self.fmcb_voltage = 0
      if self.fmcb_pb_current is None:
        self.fmcb_pb_current = 0
      if self.hall_tgt is None:
        self.hall_tgt = [0,0,0]
      if self.hall_pos is None:
        self.hall_pos = [0,0,0]
      if self.fmcb_effort is None:
        self.fmcb_effort = [0,0,0]
    else:
      self.fmcb_time = 0
      self.pp_time = 0
      self.dp_time = 0
      self.pp_tactile = [0,0,0,0,0,0]
      self.dp_tactile = [0,0,0,0,0,0,0,0,0,0,0,0]
      self.pp_strain = 0
      self.mm_accel = [0,0,0]
      self.pp_accel = [0,0,0]
      self.dp_accel = [0,0,0]
      self.mm_mag = [0,0,0]
      self.pp_mag = [0,0,0]
      self.dp_mag = [0,0,0]
      self.pp_temp = [0,0,0,0]
      self.dp_temp = [0,0,0,0]
      self.fmcb_temp = [0,0,0]
      self.fmcb_voltage = 0
      self.fmcb_pb_current = 0
      self.hall_tgt = [0,0,0]
      self.hall_pos = [0,0,0]
      self.fmcb_effort = [0,0,0]

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
      _x = self
      buff.write(_struct_3I.pack(_x.fmcb_time, _x.pp_time, _x.dp_time))
      buff.write(_struct_6H.pack(*self.pp_tactile))
      buff.write(_struct_12H.pack(*self.dp_tactile))
      buff.write(_struct_I.pack(self.pp_strain))
      buff.write(_struct_3h.pack(*self.mm_accel))
      buff.write(_struct_3h.pack(*self.pp_accel))
      buff.write(_struct_3h.pack(*self.dp_accel))
      buff.write(_struct_3H.pack(*self.mm_mag))
      buff.write(_struct_3H.pack(*self.pp_mag))
      buff.write(_struct_3H.pack(*self.dp_mag))
      buff.write(_struct_4H.pack(*self.pp_temp))
      buff.write(_struct_4H.pack(*self.dp_temp))
      buff.write(_struct_3H.pack(*self.fmcb_temp))
      _x = self
      buff.write(_struct_2H.pack(_x.fmcb_voltage, _x.fmcb_pb_current))
      buff.write(_struct_3i.pack(*self.hall_tgt))
      buff.write(_struct_3i.pack(*self.hall_pos))
      buff.write(_struct_3h.pack(*self.fmcb_effort))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 12
      (_x.fmcb_time, _x.pp_time, _x.dp_time,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 12
      self.pp_tactile = _struct_6H.unpack(str[start:end])
      start = end
      end += 24
      self.dp_tactile = _struct_12H.unpack(str[start:end])
      start = end
      end += 4
      (self.pp_strain,) = _struct_I.unpack(str[start:end])
      start = end
      end += 6
      self.mm_accel = _struct_3h.unpack(str[start:end])
      start = end
      end += 6
      self.pp_accel = _struct_3h.unpack(str[start:end])
      start = end
      end += 6
      self.dp_accel = _struct_3h.unpack(str[start:end])
      start = end
      end += 6
      self.mm_mag = _struct_3H.unpack(str[start:end])
      start = end
      end += 6
      self.pp_mag = _struct_3H.unpack(str[start:end])
      start = end
      end += 6
      self.dp_mag = _struct_3H.unpack(str[start:end])
      start = end
      end += 8
      self.pp_temp = _struct_4H.unpack(str[start:end])
      start = end
      end += 8
      self.dp_temp = _struct_4H.unpack(str[start:end])
      start = end
      end += 6
      self.fmcb_temp = _struct_3H.unpack(str[start:end])
      _x = self
      start = end
      end += 4
      (_x.fmcb_voltage, _x.fmcb_pb_current,) = _struct_2H.unpack(str[start:end])
      start = end
      end += 12
      self.hall_tgt = _struct_3i.unpack(str[start:end])
      start = end
      end += 12
      self.hall_pos = _struct_3i.unpack(str[start:end])
      start = end
      end += 6
      self.fmcb_effort = _struct_3h.unpack(str[start:end])
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
      _x = self
      buff.write(_struct_3I.pack(_x.fmcb_time, _x.pp_time, _x.dp_time))
      buff.write(self.pp_tactile.tostring())
      buff.write(self.dp_tactile.tostring())
      buff.write(_struct_I.pack(self.pp_strain))
      buff.write(self.mm_accel.tostring())
      buff.write(self.pp_accel.tostring())
      buff.write(self.dp_accel.tostring())
      buff.write(self.mm_mag.tostring())
      buff.write(self.pp_mag.tostring())
      buff.write(self.dp_mag.tostring())
      buff.write(self.pp_temp.tostring())
      buff.write(self.dp_temp.tostring())
      buff.write(self.fmcb_temp.tostring())
      _x = self
      buff.write(_struct_2H.pack(_x.fmcb_voltage, _x.fmcb_pb_current))
      buff.write(self.hall_tgt.tostring())
      buff.write(self.hall_pos.tostring())
      buff.write(self.fmcb_effort.tostring())
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
      _x = self
      start = end
      end += 12
      (_x.fmcb_time, _x.pp_time, _x.dp_time,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 12
      self.pp_tactile = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=6)
      start = end
      end += 24
      self.dp_tactile = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=12)
      start = end
      end += 4
      (self.pp_strain,) = _struct_I.unpack(str[start:end])
      start = end
      end += 6
      self.mm_accel = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.pp_accel = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.dp_accel = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.mm_mag = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 6
      self.pp_mag = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 6
      self.dp_mag = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      start = end
      end += 8
      self.pp_temp = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=4)
      start = end
      end += 8
      self.dp_temp = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=4)
      start = end
      end += 6
      self.fmcb_temp = numpy.frombuffer(str[start:end], dtype=numpy.uint16, count=3)
      _x = self
      start = end
      end += 4
      (_x.fmcb_voltage, _x.fmcb_pb_current,) = _struct_2H.unpack(str[start:end])
      start = end
      end += 12
      self.hall_tgt = numpy.frombuffer(str[start:end], dtype=numpy.int32, count=3)
      start = end
      end += 12
      self.hall_pos = numpy.frombuffer(str[start:end], dtype=numpy.int32, count=3)
      start = end
      end += 6
      self.fmcb_effort = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_6H = struct.Struct("<6H")
_struct_3H = struct.Struct("<3H")
_struct_3i = struct.Struct("<3i")
_struct_12H = struct.Struct("<12H")
_struct_3I = struct.Struct("<3I")
_struct_3h = struct.Struct("<3h")
_struct_4H = struct.Struct("<4H")
_struct_2H = struct.Struct("<2H")
