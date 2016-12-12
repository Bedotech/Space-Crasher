class Texture
{
  public:
    Texture();
    ~Texture();

    /**
     * Load image from specific path.
     * @param  path
     *   The path of image.
     * @return
     *   Return true if the image is loaded correctly.
     */
    bool loadFromFile( std::string path );

    #ifdef _SDL_TTF_H
    /**
     * Create TTF text from string.
     * @param  textureText
     *   String of the text to render.
     * @param  textColor
     *   Color of the text.
     * @return
     *   Return true if text is rendered correctly.
     */
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif

    /**
     * Destroy the texture.
     */
    void free();

    /**
     * Set an additional color value multiplied into render copy operations.
     *
     * @param red
     *   Value of red.
     * @param green
     *   Value of green.
     * @param blue
     *   Value of blue.
     */
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    /**
     * Set the blended mode.
     *
     * @param blending
     *   Set the docs for varius blendend mod.
     */
    void setBlendMode( SDL_BlendMode blending );

    /**
     * Set the alpa value multiplied into render copy operation.
     *
     * @param alpha
     *   Value of alpha.
     */
    void setAlpha( Uint8 alpha );

    /**
     * Copy a portion of the texture to the current rendering target.
     *
     * @param x
     * @param y
     * @param clip
     *   An SDL_Rect structure, NULL for the enteire texture.
     * @param angle
     *   Angle in degrees, that indicate the rotation.
     * @param center
     *    A SDL_Point indicate the center of the rotation.
     * @param flip
     *   A SDL_RendererFlip that indicate the flip of texture.
     */
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    /**
     * Return the width of texture object.
     *
     * @return
     *   Value of the width.
     */
    int getWidth();

    /**
     * Return the height of texture object.
     *
     * @return
     *   Value of the height.
     */
    int getHeight();

  private:
    SDL_Texture* texture;

    int width;
    int height;
};
