#include "Skybox.h"

void Skybox::loadSkybox() {
	backSide =
	SOIL_load_OGL_texture(
		"textures/ame_nebula/purplenebula_bk.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_COMPRESS_TO_DXT
		);

	bottomSide =
	SOIL_load_OGL_texture(
		"textures/ame_nebula/purplenebula_dn.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_COMPRESS_TO_DXT
		);

	frontSide =
	SOIL_load_OGL_texture(
		"textures/ame_nebula/purplenebula_ft.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_COMPRESS_TO_DXT
		);

	leftSide =
	SOIL_load_OGL_texture(
		"textures/ame_nebula/purplenebula_lf.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_COMPRESS_TO_DXT
		);

	rightSide =
	SOIL_load_OGL_texture(
		"textures/ame_nebula/purplenebula_rt.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_COMPRESS_TO_DXT
		);

	topSide =
	SOIL_load_OGL_texture(
		"textures/ame_nebula/purplenebula_up.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_COMPRESS_TO_DXT
		);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void Skybox::draw() {
	glPushMatrix(); {
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, backSide);
		glPushMatrix();{
			glBegin(GL_QUADS);{
				glTexCoord2d(0.0,0.0); glVertex3d(size,-size,size );
				glTexCoord2d(1.0,0.0); glVertex3d(-size,-size,size);
				glTexCoord2d(1.0,1.0); glVertex3d(-size,size,size);
				glTexCoord2d(0.0,1.0); glVertex3d(size,size,size);
			}glEnd();
		}
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, frontSide);
		glPushMatrix();{
			glBegin( GL_QUADS );{
				glTexCoord2d(0.0,0.0); glVertex3d(-size,-size,-size );
				glTexCoord2d(1.0,0.0); glVertex3d(size,-size,-size);
				glTexCoord2d(1.0,1.0); glVertex3d(size,size,-size);
				glTexCoord2d(0.0,1.0); glVertex3d(-size,size,-size);
			}glEnd();
		}glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, leftSide);
		glPushMatrix();{
			glBegin(GL_QUADS);{
				glTexCoord2d(0.0,0.0); glVertex3d(size,-size,-size );
				glTexCoord2d(1.0,0.0); glVertex3d(size,-size,size);
				glTexCoord2d(1.0,1.0); glVertex3d(size,size,size);
				glTexCoord2d(0.0,1.0); glVertex3d(size,size,-size);
			}glEnd();
		}
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, rightSide);
		glPushMatrix();{
			glBegin(GL_QUADS);{
				glTexCoord2d(0.0,0.0); glVertex3d(-size,-size,size );
				glTexCoord2d(1.0,0.0); glVertex3d(-size,-size,-size);
				glTexCoord2d(1.0,1.0); glVertex3d(-size,size,-size);
				glTexCoord2d(0.0,1.0); glVertex3d(-size,size,size);
			}glEnd();
		}glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, bottomSide);
		glPushMatrix();{
			glBegin(GL_QUADS);{
				glTexCoord2d(0.0,0.0); glVertex3d(size,-size,size );
				glTexCoord2d(0.0,1.0); glVertex3d(-size,-size,size);
				glTexCoord2d(1.0,1.0); glVertex3d(-size,-size,-size);
				glTexCoord2d(1.0,0.0); glVertex3d(size,-size,-size);
			}glEnd();
		}glPopMatrix();


		glBindTexture(GL_TEXTURE_2D, topSide);
		glPushMatrix();{
			glBegin(GL_QUADS);{
				glTexCoord2d(0.0,0.0); glVertex3d(-size,size,size );
				glTexCoord2d(1.0,0.0); glVertex3d(-size,size,-size);
				glTexCoord2d(1.0,1.0); glVertex3d(size,size,-size);
				glTexCoord2d(0.0,1.0); glVertex3d(size,size,size);
			}glEnd();
		}glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	} glPopMatrix();
}

int Skybox::getSize() {
	return size;
}
