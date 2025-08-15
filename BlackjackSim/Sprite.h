/*
* @file Sprite.h
* @brief Header file for the Sprite class and its derived classes.
* 
* This file defines the Sprite class, which serves as a base class for various types of sprites
* in the blackjack simulation. It includes functionality for rendering sprites with textures,
* checking for clicks, and managing visibility. The Button and Chip classes inherit
* from Sprite and provide additional functionality specific to their types.
* 
* @author Michael Lintelman
* @date 2024-04-01
*/

#pragma once
#include <GL/glut.h>

class Sprite {
protected:
    int left = 0;
    int top = 0;
    int width = 0;
    int height = 0;
    GLuint texture = 0;
    bool visible = true;

public:
    Sprite(int x, int y, int w, int h, GLuint tex)
        : left(x), top(y), width(w), height(h), texture(tex) {
    }
    Sprite(int x, int y, int w, int h)
        : left(x), top(y), width(w), height(h), texture(0) { // Default texture is 0 (no texture)
	}

    GLuint getTexture() const { return texture; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setVisible(bool v) { visible = v; }
	void setTexture(GLuint tex) { texture = tex; }

    bool checkClick(int clickX, int clickY) const {
        return visible && clickX >= left && clickX <= left + width &&
            clickY <= top && clickY >= top - height;
    }

    // Draw the sprite using its stored texture
    virtual void draw() const {
        if (!visible) return;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(left, top);                  // top-left
        glTexCoord2i(1, 1); glVertex2i(left + width, top);          // top-right
        glTexCoord2i(1, 0); glVertex2i(left + width, top - height); // bottom-right
        glTexCoord2i(0, 0); glVertex2i(left, top - height);         // bottom-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
    // Overloaded draw function (uses given x/y)
    virtual void draw(int x, int y) const {
        if (!visible) return;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(x, y);                  // top-left
        glTexCoord2i(1, 1); glVertex2i(x + width, y);          // top-right
        glTexCoord2i(1, 0); glVertex2i(x + width, y - height); // bottom-right
        glTexCoord2i(0, 0); glVertex2i(x, y - height);         // bottom-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
};

class Button : public Sprite {
public:
    // Constructor with texture
    Button(int x, int y, GLuint tex)
        : Sprite(x, y, 128, 64, tex) {
    }

    // Constructor without texture
    Button(int x, int y)
        : Sprite(x, y, 128, 64, 0) { // Default texture is 0 (no texture)
    }

    void write(GLfloat x, GLfloat y, const char* message, float scale) const {
        glColor3f(0.0f, 0.0f, 0.0f);
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(scale, scale, scale);
        for (int i = 0; i < strlen(message); ++i)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, message[i]);
        glPopMatrix();
    }
};


class Chip : public Sprite {
public:
    // Constructor with texture
    Chip(int x, int y, GLuint tex)
        : Sprite(x, y, 64, 72, tex) {
    }
    // Constructor without texture
    Chip(int x, int y)
        : Sprite(x, y, 64, 72, 0) { // Default texture is 0 (no texture)
    }
};