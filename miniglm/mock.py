'''
    miniglm mock
'''

class Vec2:
    def __init__(self, iterable):
        pass

    @property
    def length(self) -> float:
        '''
            float: length
        '''

    @property
    def normal(self) -> 'Vec2':
        '''
            Vec2: normal
        '''

    @property
    def tup(self) -> tuple:
        '''
            tuple: tuple
        '''

    def dot(self, rhs) -> float:
        '''
            Args:
                rhs (Vec2): rhs

            Returns:
                float: dot product
        '''

    def reflect(self, norm) -> 'Vec2':
        '''
            Args:
                norm (Vec2): norm

            Returns:
                Vec2: reflect
        '''

    def refract(self, norm, eta) -> 'Vec2':
        '''
            Args:
                norm (Vec2): norm
                eta (float): eta

            Returns:
                Vec2: refract
        '''

class Vec3:
    def __init__(self, iterable):
        pass

    @property
    def length(self) -> float:
        '''
            float: length
        '''

    @property
    def normal(self) -> 'Vec3':
        '''
            Vec3: normal
        '''

    @property
    def tup(self) -> tuple:
        '''
            tuple: tuple
        '''

    def dot(self, rhs) -> float:
        '''
            Args:
                rhs (Vec3): rhs

            Returns:
                float: dot product
        '''

    def cross(self, rhs) -> 'Vec3':
        '''
            Args:
                rhs (Vec3): rhs

            Returns:
                Vec3: cross product
        '''

    def reflect(self, norm) -> 'Vec3':
        '''
            Args:
                norm (Vec3): norm

            Returns:
                Vec3: reflect
        '''

    def refract(self, norm, eta) -> 'Vec3':
        '''
            Args:
                norm (Vec3): norm
                eta (float): eta

            Returns:
                Vec3: refract
        '''

class Vec4:
    def __init__(self, iterable):
        pass

    @property
    def length(self) -> float:
        '''
            float: length
        '''

    @property
    def normal(self) -> 'Vec4':
        '''
            Vec4: normal
        '''

    @property
    def tup(self) -> tuple:
        '''
            tuple: tuple
        '''

    def dot(self, rhs) -> float:
        '''
            Args:
                rhs (Vec4): rhs

            Returns:
                float: dot product
        '''

    def reflect(self, norm) -> 'Vec4':
        '''
            Args:
                norm (Vec4): norm

            Returns:
                Vec4: reflect
        '''

    def refract(self, norm, eta) -> 'Vec4':
        '''
            Args:
                norm (Vec4): norm
                eta (float): eta

            Returns:
                Vec4: refract
        '''

class Mat2:
    def __init__(self, iterable):
        pass

    @property
    def trans(self) -> 'Mat2':
        '''
            Mat2: transpose
        '''

    @property
    def det(self) -> float:
        '''
            float: determinant
        '''
    @property
    def inv(self) -> 'Mat2':
        '''
            Mat2: inverse
        '''
    @property
    def tup(self) -> tuple:
        '''
            Mat2: tuple
        '''

    def row(self, i) -> Vec2:
        '''
            Args:
                i (int): i

            Returns:
                Vec2: row
        '''

    def col(self, i) -> Vec2:
        '''
            Args:
                i (int): i

            Returns:
                Vec2: column
        '''

class Mat3:
    def __init__(self, iterable):
        pass

    @property
    def trans(self):
        '''
            Mat3: transpose
        '''

    @property
    def det(self):
        '''
            float: determinant
        '''
    @property
    def inv(self):
        '''
            Mat3: inverse
        '''
    @property
    def tup(self) -> tuple:
        '''
            Mat3: tuple
        '''

    def row(self, i) -> Vec3:
        '''
            Args:
                i (int): i

            Returns:
                Vec3: row
        '''

    def col(self, i) -> Vec3:
        '''
            Args:
                i (int): i

            Returns:
                Vec3: column
        '''

class Mat4:
    def __init__(self, iterable):
        pass

    @property
    def trans(self):
        '''
            Mat4: transpose
        '''

    @property
    def det(self):
        '''
            float: determinant
        '''
    @property
    def inv(self):
        '''
            Mat4: inverse
        '''
    @property
    def tup(self) -> tuple:
        '''
            Mat4: tuple
        '''

    def row(self, i) -> Vec4:
        '''
            Args:
                i (int): i

            Returns:
                Vec4: row
        '''

    def col(self, i) -> Vec4:
        '''
            Args:
                i (int): i

            Returns:
                Vec4: column
        '''

class Quat:
    def __init__(self, iterable):
        pass

    @property
    def length(self) -> float:
        '''
            float: length
        '''

    @property
    def normal(self) -> 'Quat':
        '''
            Quat: normal
        '''

    @property
    def conj(self) -> 'Quat':
        '''
            Quat: conj
        '''

    @property
    def inv(self) -> 'Quat':
        '''
            Quat: inv
        '''

    @property
    def tup(self) -> tuple:
        '''
            tuple: tup
        '''

    def dot(self, rhs) -> float:
        '''
            Args:
                rhs (Quat): rhs

            Returns:
                float: dot product
        '''

    def cross(self, rhs) -> 'Quat':
        '''
            Args:
                rhs (Quat): rhs

            Returns:
                Quat: cross product
        '''

    def slerp(self, rhs, coef) -> 'Quat':
        '''
            Args:
                rhs (Quat): rhs
                coef (float): coefficient

            Returns:
                Quat: slerp
        '''

def mat4_perspective(fovy, ratio, znear, zfar) -> Mat4:
    '''
        Args:
            fovy (float): fovy
            ratio (float): ratio
            znear (float): znear
            zfar (float): zfar

        Returns:
            Mat4: perspective
    '''

def mat4_ortho(left, right, bottom, top, znear, zfar) -> Mat4:
    '''
        Args:
            left (float): left
            right (float): right
            bottom (float): bottom
            top (float): top
            znear (float): znear
            zfar (float): zfar

        Returns:
            Mat4: ortho
    '''

def mat4_look_at(eye, center, up) -> Mat4:
    '''
        Args:
            eye (Vec3): eye
            center (Vec3): center
            up (Vec3): up

        Returns:
            Mat4: look_at
    '''
