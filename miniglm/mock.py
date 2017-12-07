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

    @property
    def data(self) -> bytes:
        '''
            bytes: data
        '''

    def dot(self, rhs: 'Vec2') -> float:
        '''
            Args:
                rhs (Vec2): rhs

            Returns:
                float: dot product
        '''

    def reflect(self, norm: 'Vec2') -> 'Vec2':
        '''
            Args:
                norm (Vec2): norm

            Returns:
                Vec2: reflect
        '''

    def refract(self, norm: 'Vec2', eta: float) -> 'Vec2':
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

    @property
    def data(self) -> bytes:
        '''
            bytes: data
        '''

    def dot(self, rhs: 'Vec3') -> float:
        '''
            Args:
                rhs (Vec3): rhs

            Returns:
                float: dot product
        '''

    def cross(self, rhs: 'Vec3') -> 'Vec3':
        '''
            Args:
                rhs (Vec3): rhs

            Returns:
                Vec3: cross product
        '''

    def reflect(self, norm: 'Vec3') -> 'Vec3':
        '''
            Args:
                norm (Vec3): norm

            Returns:
                Vec3: reflect
        '''

    def refract(self, norm: 'Vec3', eta: float) -> 'Vec3':
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

    @property
    def data(self) -> bytes:
        '''
            bytes: data
        '''

    def dot(self, rhs: 'Vec4') -> float:
        '''
            Args:
                rhs (Vec4): rhs

            Returns:
                float: dot product
        '''

    def reflect(self, norm: 'Vec4') -> 'Vec4':
        '''
            Args:
                norm (Vec4): norm

            Returns:
                Vec4: reflect
        '''

    def refract(self, norm: 'Vec4', eta: float) -> 'Vec4':
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

    @property
    def data(self) -> bytes:
        '''
            bytes: data
        '''

    def row(self, i: int) -> 'Vec2':
        '''
            Args:
                i (int): i

            Returns:
                Vec2: row
        '''

    def col(self, i: int) -> 'Vec2':
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
    def trans(self) -> 'Mat3':
        '''
            Mat3: transpose
        '''

    @property
    def det(self) -> float:
        '''
            float: determinant
        '''
    @property
    def inv(self) -> 'Mat3':
        '''
            Mat3: inverse
        '''
    @property
    def tup(self) -> tuple:
        '''
            Mat3: tuple
        '''

    @property
    def data(self) -> bytes:
        '''
            bytes: data
        '''

    def row(self, i: int) -> 'Vec3':
        '''
            Args:
                i (int): i

            Returns:
                Vec3: row
        '''

    def col(self, i: int) -> 'Vec3':
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
    def trans(self) -> 'Mat4':
        '''
            Mat4: transpose
        '''

    @property
    def det(self) -> float:
        '''
            float: determinant
        '''
    @property
    def inv(self) -> 'Mat4':
        '''
            Mat4: inverse
        '''
    @property
    def tup(self) -> tuple:
        '''
            Mat4: tuple
        '''

    @property
    def data(self) -> bytes:
        '''
            bytes: data
        '''

    def row(self, i: int) -> 'Vec4':
        '''
            Args:
                i (int): i

            Returns:
                Vec4: row
        '''

    def col(self, i: int) -> 'Vec4':
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
    def axis(self) -> 'Vec3':
        '''
            Vec3: axis
        '''

    @property
    def angle(self) -> float:
        '''
            float: angle
        '''

    @property
    def tup(self) -> tuple:
        '''
            tuple: tup
        '''

    @property
    def data(self) -> bytes:
        '''
            bytes: data
        '''

    def dot(self, rhs: 'Quat') -> float:
        '''
            Args:
                rhs (Quat): rhs

            Returns:
                float: dot product
        '''

    def cross(self, rhs: 'Quat') -> 'Quat':
        '''
            Args:
                rhs (Quat): rhs

            Returns:
                Quat: cross product
        '''

    def slerp(self, rhs: 'Quat', coef: float) -> 'Quat':
        '''
            Args:
                rhs (Quat): rhs
                coef (float): coefficient

            Returns:
                Quat: slerp
        '''

    def lerp(self, rhs: 'Quat', coef: float) -> 'Quat':
        '''
            Args:
                rhs (Quat): rhs
                coef (float): coefficient

            Returns:
                Quat: slerp
        '''

def mat4_perspective(fovy: float, ratio: float, znear: float, zfar: float) -> 'Mat4':
    '''
        Args:
            fovy (float): fovy
            ratio (float): ratio
            znear (float): znear
            zfar (float): zfar

        Returns:
            Mat4: perspective
    '''

def mat4_ortho(left: float, right: float, bottom: float, top: float, znear: float, zfar: float) -> 'Mat4':
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

def mat4_look_at(eye: 'Vec3', center: 'Vec3', up: 'Vec3') -> 'Mat4':
    '''
        Args:
            eye (Vec3): eye
            center (Vec3): center
            up (Vec3): up

        Returns:
            Mat4: look_at
    '''


def radians(deg: float) -> float:
    '''
        Args:
            deg (float): degrees

        Returns:
            float: degrees converted to radians
    '''


def degrees(rad: float) -> float:
    '''
        Args:
            rad (float): radians

        Returns:
            float: radians converted to degrees
    '''
