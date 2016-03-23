#include "precomp.h"
#include "CoordinateHelper.h"
#include "Rectangle.h"


Rectangle::Rectangle(GLfloat left, GLfloat top, GLfloat width, GLfloat height, float32 density)
{
  this->SetBounds(left, top, width, height);
  _density = density;
}

Rectangle::~Rectangle()
{
  _body = nullptr;
}

void Rectangle::SetBounds(GLfloat left, GLfloat top, GLfloat width, GLfloat height)
{
  _left = left;
  //_top = CoordinateHelper::getGameHeight() - top; // Invert the y-coodinate
  _top = top;
  _width = width;
  _height = height; 
}

bool Rectangle::Update() {

  if (_buffer) {
    delete _buffer;
  }

  //if (_density > 5.0) {
  //std::cout << "Applying a force" << std::endl;
    //_body->ApplyForce(b2Vec2(50, 50), _body->GetWorldCenter(), true);
    //}

  if (_body) {
    b2Vec2 pos = _body->GetPosition();
    _left = pos.x;
    _top = -pos.y;
    //std::cout << "Top = " << _top << std::endl;
  }

  _numVertices = RECTANGLE_VERTICES_COUNT;
  _bufferSize = _numVertices * 3;
  //std::cout << _bufferSize << std::endl;

  GLfloat fLeft   = CoordinateHelper::TranslateXToOpenGL(_left);
  GLfloat fWidth  = CoordinateHelper::TranslateXToOpenGL(_width, true);
  GLfloat fTop    = CoordinateHelper::TranslateYToOpenGL(_top);
  GLfloat fHeight = CoordinateHelper::TranslateYToOpenGL(_height, true);

  //std::cout << "Params = (" << fTop << ", " << fLeft << ", " << fWidth << ", " << fHeight << ")" << std::endl;

  _buffer = new GLfloat[_bufferSize] {
    fLeft, fTop, 0.0f,
    fLeft, fTop - fHeight, 0.0f,
    fLeft + fWidth, fTop - fHeight, 0.0f,
    fLeft + fWidth, fTop - fHeight, 0.0f,
    fLeft + fWidth, fTop, 0.0f,
    fLeft, fTop, 0.0f
  };

  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _bufferSize * sizeof(GLfloat), _buffer, GL_STATIC_DRAW);

  return true;
}

bool Rectangle::Initialize()
{
  //Initialize the physics geometry
  b2BodyDef bodyDef;
  if (_density > 11.0f) {
    bodyDef.type = b2_dynamicBody;
  }

  bodyDef.position.Set(_left, _top);

  _body = world.CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(_width, _height);

  std::cout << "Density = " << _density << std::endl;
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f; //_density;
  fixtureDef.friction = 0.3f; //1 / _density;
  fixtureDef.restitution = 0.2f;

  b2MassData mass;
  mass.mass = _density * 10.0;
  mass.center = b2Vec2(0.0f, 0.0f);
  mass.I = 0;

  _body->SetMassData(&mass);

  if (_body) {
    _body->CreateFixture(&fixtureDef);
  }
  else {
    std::cout << "Error creating box2d body" << std::endl;
  }

  if (_density > 11.0) {
  //std::cout << "Applying a force" << std::endl;
    _body->SetLinearVelocity(b2Vec2(_density, -10*_density));
  }
  //b2Vec2 v = _body->GetWorldVector(b2Vec2(_density, -4*_density));
  // b2Vec2 v = _body->GetWorldVector(b2Vec2(0.0f, -200.0f));
  // std::cout << "Vector is (" << v.x << ", " << v.y << ")" << std::endl;
  //   _body->ApplyForce(v, _body->GetWorldCenter(), true);
  //   std::cout << "Linear = " << _density << ", " << -4*_density << std::endl;
  //   std::cout << "Body = " << _body << std::endl;
    //}

  
  // for (int i=0; i < _bufferSize; i++)
  //   {
  //     std::cout << _buffer[i] << " ";

  //     if (((i + 1) % 3) == 0) {
  //       std::cout << std::endl;
  //     }
  //   }

  // std::cout << std::endl;

  _numVertices = RECTANGLE_VERTICES_COUNT;
  _bufferSize = _numVertices * 3;
  std::cout << _bufferSize << std::endl;

 	glGenBuffers(1, &_vertexBuffer);
	return true;
}
