INTEGER, PLUS, MINUS, DIV, MULT, EOF, LPAREN, RPAREN = 'INTEGER', 'PLUS', 'MINUS', 'DIV', 'MULT', 'EOF', 'LPAREN', 'RPAREN'

class Token:
    def __init__(self, typee, value):
        self.type = typee;
        self.value = value;

    def __str__(self):
        return 'Token({typee}, {value})'.format(typee = self.type, value = repr(self.value))

    def __repr__(self):
        return self.__str__()

class Lexer:
    def __init__(self,text):
        self.text = text
        self.pos = 0
        self.current_char = self.text[self.pos]

    def error(self):
        raise Exception('Invalid character')

    def advance(self):
        self.pos += 1
        if self.pos > len(self.text)-1:
            self.current_char = None
        else:
            self.current_char = self.text[self.pos]

    def skip_whitespace(self):
        while self.current_char is not None and self.current_char.isspace():
            self.advance()

    def integer(self):
        result = ''
        while self.current_char is not None and self.current_char.isdigit():
            result += self.current_char
            self.advance()
        return int(result)

    def get_next_token(self):
        if self.current_char is None:
            return Token(EOF, None)

        if self.current_char.isspace():
            self.skip_whitespace()

        if self.current_char.isdigit():
            return Token(INTEGER, self.integer())

        if self.current_char == '+':
            self.advance()
            return Token(PLUS, '+')

        if self.current_char == '-':
            self.advance()
            return Token(MINUS, '-')

        if self.current_char == '(':
            self.advance()
            return Token(LPAREN, '(')

        if self.current_char == ')':
            self.advance()
            return Token(RPAREN, ')')
        
        if self.current_char == '/':
            self.advance()
            return Token(DIV, '/')

        if self.current_char == '*':
            self.advance()
            return Token(MULT, '*')
        self.error()

class Parser:
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = self.lexer.get_next_token()

    def error(self):
        raise Exception('Invalid syntax')

    def eat(self, token_type):
        if self.current_token.type == token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            self.error()

    def factor(self):
        token = self.current_token
        if token.type is INTEGER:
            self.eat(INTEGER)
        elif token.type is LPAREN:
            self.eat(LPAREN)
            self.expr()
            self.eat(RPAREN)
        else:
            self.error()

    def term(self):
        self.factor()

        while self.current_token.type in (DIV, MULT):
            token = self.current_token
            if token.type is DIV:
                self.eat(DIV)
                self.factor()
            elif token.type is MULT:
                self.eat(MULT)
                self.factor()

    def expr(self):
        self.term()

        while self.current_token.type in (PLUS, MINUS):
            token = self.current_token
            if token.type is PLUS:
                self.eat(PLUS)
                self.term()
            elif token.type is MINUS:
                self.eat(MINUS)
                self.term()

    def parse(self):
        self.expr()

def main():
    while True:
        try:
            text = input('calc> ')
        except EOFError:
            break
        if not text:
            continue
        parser = Parser(Lexer(text))
        parser.parse()

if __name__ == '__main__':
    main()
