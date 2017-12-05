import inspect
import re

from miniglm.mock import (
    Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat, mat4_perspective, mat4_ortho, mat4_look_at, radians, degrees,
)

other_methods = (mat4_perspective, mat4_ortho, mat4_look_at, radians, degrees)
types = (Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat)


def decorate(extra):
    extra = extra.replace('\'', '').replace('self, ', '').replace('(self)', '').replace('>', '&gt;').replace(' ', '&nbsp;')
    extra = re.sub(r'(\-&gt;)&nbsp;(.+)', r'<div class="Arrow">\1</div> <div class="RetType">\2</div>', extra)
    extra = re.sub(r':([^\),]+)', r':<div class="ParamType">\1</div>', extra)
    extra = re.sub(r'(\(|\))', r'<div class="Parentheses">\1</div>', extra)
    return extra


for typ in types:
    members = filter(lambda x: not x.startswith('_'), dir(typ))

    meths = []
    attrs = []

    for member in members:
        if callable(getattr(typ, member)):
            meths.append((member, str(inspect.signature(getattr(typ, member)))))

        else:
            attrs.append((member, str(inspect.signature(getattr(typ, member).fget))))

    print(f'<div class="Class">')
    print(f'<div class="ClassName">{typ.__name__}</div>')
    print(f'<div class="ClassMembers">')
    for member, extra in meths + attrs:
        extra = decorate(extra)
        member = f'<div class="Member">{member}</div>'
        print(f'<div class="ClassMember">{member}{extra}</div>')
    print(f'</div>')
    print(f'</div>')


print(f'<div class="Class Others">')
print(f'<div class="ClassName">Other methods</div>')
print(f'<div class="ClassMembers">')
for member, extra in [(m.__name__, str(inspect.signature(m))) for m in other_methods]:
    extra = decorate(extra)
    member = f'<div class="Member">{member}</div>'
    print(f'<div class="ClassMember">{member}{extra}</div>')
print(f'</div>')
print(f'</div>')
