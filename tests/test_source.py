import os
import re
import unittest

from common import MyTestCase

files = []
src = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'src'))
for filename in filter(os.path.isfile, [os.path.join(src, f) for f in os.listdir(src)]):
    with open(filename) as f:
        files.append({
            'name': filename,
            'body': f.read().splitlines(),
        })


def foreach_match(pattern):
    for f in files:
        for i, line in enumerate(f['body']):
            match = re.compile(pattern).search(line)
            if match:
                yield (f['name'], i, match)


def error(errors, name, line, cursor):
    errors.append('%s:%d:%d' % (name, line + 1, cursor + 1))


class TestCase(MyTestCase):
    def test_indent_with_spaces(self):
        errors = []
        for name, line, match in foreach_match(r'^\t*( )\t*'):
            error(errors, name, line, match.start(0))
        self.assertNoErrors(errors, 'SPACE IN INDENTATION')

    def test_space_before_curly_braces(self):
        errors = []
        for name, line, match in foreach_match(r'[^\s]\{'):
            error(errors, name, line, match.start(0))
        self.assertNoErrors(errors, 'NO SPACE BEFORE CURLY BRACE')

    def test_double_space(self):
        errors = []
        for name, line, match in foreach_match(r'  '):
            error(errors, name, line, match.start(0))
        self.assertNoErrors(errors, 'DOUBLE SPACE')

    def test_space_before_comma(self):
        errors = []
        for name, line, match in foreach_match(r'\s,'):
            error(errors, name, line, match.start(0))
        self.assertNoErrors(errors, 'SPACE BEFORE COMMA')

    def test_space_before_comment(self):
        errors = []
        for name, line, match in foreach_match(r'[^\s]//'):
            error(errors, name, line, match.start(0))
        self.assertNoErrors(errors, 'NO SPACE BEFORE COMMENT')


if __name__ == '__main__':
    unittest.main()
