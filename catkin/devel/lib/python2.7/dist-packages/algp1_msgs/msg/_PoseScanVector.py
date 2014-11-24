"""autogenerated by genpy from algp1_msgs/PoseScanVector.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import algp1_msgs.msg
import geometry_msgs.msg

class PoseScanVector(genpy.Message):
  _md5sum = "630b2b0ca1c5d59f453e5c5806f5c1ac"
  _type = "algp1_msgs/PoseScanVector"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """algp1_msgs/PoseScan[] scans
================================================================================
MSG: algp1_msgs/PoseScan
# Pose for x, y, theta
geometry_msgs/Pose2D pose2d

# Array of float32s for ranges (is a vector)
float32[] ranges
================================================================================
MSG: geometry_msgs/Pose2D
# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta
"""
  __slots__ = ['scans']
  _slot_types = ['algp1_msgs/PoseScan[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       scans

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(PoseScanVector, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.scans is None:
        self.scans = []
    else:
      self.scans = []

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
      length = len(self.scans)
      buff.write(_struct_I.pack(length))
      for val1 in self.scans:
        _v1 = val1.pose2d
        _x = _v1
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.theta))
        length = len(val1.ranges)
        buff.write(_struct_I.pack(length))
        pattern = '<%sf'%length
        buff.write(struct.pack(pattern, *val1.ranges))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.scans is None:
        self.scans = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.scans = []
      for i in range(0, length):
        val1 = algp1_msgs.msg.PoseScan()
        _v2 = val1.pose2d
        _x = _v2
        start = end
        end += 24
        (_x.x, _x.y, _x.theta,) = _struct_3d.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sf'%length
        start = end
        end += struct.calcsize(pattern)
        val1.ranges = struct.unpack(pattern, str[start:end])
        self.scans.append(val1)
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
      length = len(self.scans)
      buff.write(_struct_I.pack(length))
      for val1 in self.scans:
        _v3 = val1.pose2d
        _x = _v3
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.theta))
        length = len(val1.ranges)
        buff.write(_struct_I.pack(length))
        pattern = '<%sf'%length
        buff.write(val1.ranges.tostring())
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.scans is None:
        self.scans = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.scans = []
      for i in range(0, length):
        val1 = algp1_msgs.msg.PoseScan()
        _v4 = val1.pose2d
        _x = _v4
        start = end
        end += 24
        (_x.x, _x.y, _x.theta,) = _struct_3d.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sf'%length
        start = end
        end += struct.calcsize(pattern)
        val1.ranges = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=length)
        self.scans.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3d = struct.Struct("<3d")
