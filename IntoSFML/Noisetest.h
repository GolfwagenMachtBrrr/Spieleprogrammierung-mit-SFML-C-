#pragma once
#include "Common.h"
#include "Agent.h"

class Agent
{
public:
	void Init(int x, int y)
	{
		Vector2f nPosition(x, y);

		mBody.setPosition(nPosition);
		mBody.setSize(Vector2f(1, 1));
		mBody.setFillColor(sf::Color::White);


		mVelocity.x = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f, mVelocity.y = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
		
		std::cout << mVelocity.x << " " << mVelocity.y << endl;

		mAcceleration = Vector2f(0, 0);
	}
	
	void Guide(vector<shared_ptr<Agent>>& nOther)
	{
		mAcceleration.x = 0, mAcceleration.y = 0; 
		SteerAgentSteer(nOther); 
	}

	void Update()
	{
		mPosition = mBody.getPosition();
		mVelocity += mAcceleration;

		CheckVelocity(); 

		mBody.move(mVelocity);

		mPosition.x = ((int)mPosition.x + mWidth) % mWidth;
		mPosition.y = ((int)mPosition.y + mHeight) % mHeight;

	}

	void Draw(RenderWindow& nWindow)
	{
		nWindow.draw(mBody);
	}

	void CheckVelocity()
	{
		if (mVelocity.x >= mMaxSpeed)
		{
			mVelocity.x = mMaxSpeed;
		}

		if (mVelocity.y >= mMaxSpeed)
		{
			mVelocity.y = mMaxSpeed;
		}
	}

	void CheckForce(Vector2f& vec)
	{
		if (vec.x >= mMaxForce)
		{
			vec.x = mMaxForce;
		}

		if (vec.y >= mMaxForce)
		{
			vec.y = mMaxForce;
		}
	}

	void SteerAgentSteer(vector<shared_ptr<Agent>>& nOthers)
	{
		Vector2f nSumAlign(0, 0);
		Vector2f nSumCohere(0, 0);
		Vector2f nSumSeperate(0, 0); 

		int nCountN = 0, nCountS = 0; 
		for (auto& nOther : nOthers)
		{
			float d = Utility::CalculateDistance(mPosition, nOther->GetPosition());

			if (d > 0 && d < mNeighborDist)
			{
				nSumAlign += nOther->GetVelocity();
				nSumCohere += nOther->GetPosition(); 
				nCountN++;
			}

			if (d > 0 && d < mNeighborDist)
			{
				Vector2f nPositionDiff =  (nOther->GetPosition() - mPosition);
				Utility::Normalize(nPositionDiff); 

				nPositionDiff.x /= d; nPositionDiff.y /= d;
				nSumSeperate += nPositionDiff; 

				nCountS++;
			}

			if (nCountS > 0)
			{
				Target(nSumSeperate, mSeperateK); 
			}


		}

	}


	void Target(Vector2f nTargetDir, float k)
	{
		// LOL
		Utility::Normalize(nTargetDir); 
		nTargetDir.x *= mMaxSpeed; nTargetDir.y += mMaxSpeed; 
		nTargetDir -= mVelocity;
		CheckForce(nTargetDir); 
		nTargetDir.x *= k; nTargetDir.y += k;
		mAcceleration += nTargetDir; 
	}

	



public:
	void SetWindowSize(int x, int y) { mWidth = x, mHeight = y; }
	void SetMaxSpeed(int x) { mMaxSpeed = x; }

	Vector2f GetPosition() { return mPosition; }
	Vector2f GetVelocity() { return mVelocity; }

private:
	RectangleShape mBody;
	Vector2f mVelocity;
	Vector2f mAcceleration;
	Vector2f mPosition;

	float mMaxSpeed = 1.0f / 128.0f*2;
	float mMaxForce = 0.03f;
	int mNeighborDist = 100, mSperateDist = 50; 
	float mSeperateK = 1.8;
	int mWidth, mHeight;

public:

	Agent() = default;
};

class FlockTest
{
public: 
	void Start()
	{
		mWindow.create(sf::VideoMode(mWidth, mHeight), "Flock");
		OnCreate();

		while (mWindow.isOpen())
		{
			sf::Event event;
			while (mWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					mWindow.close();
				}

			}
			mWindow.clear(sf::Color::Black);

			OnUpdate();
			Draw(mWindow); 
	
			mWindow.display();
		}
	}

private: 

	void OnCreate()
	{
		for (int i = 0; i < 100; i++)
		{
			int nRandX = rand() % mWidth + 10, nRandY = rand() % mHeight + 10; 
			shared_ptr<Agent> nAgent = make_shared<Agent>();
			nAgent->Init(nRandX,nRandY);
			nAgent->SetWindowSize(mWidth, mHeight); 
			mAgents.push_back(nAgent); 
		}

	}
	void OnUpdate()
	{
		for (auto& nAgent : mAgents) { nAgent->Update();}
	}
	
	void Draw(RenderWindow& nWindow) {
		for (auto& nAgent : mAgents) { nAgent->Draw(nWindow); }
	}


private:
	RenderWindow mWindow; 
	int mWidth = 256*4, mHeight = 256 * 4;

	vector<shared_ptr<Agent>> mAgents; 

};

class TestNoise
{
public: 
	void Start()
	{
		m_window.create(sf::VideoMode(m_sizeX, m_sizeY), "Perlin");
		OnCreate(); 

		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
				}

			}
			m_window.clear(sf::Color::Black);

			OnUpdate();

			nMapTexture.loadFromImage(m_map);
			nMapSprite.setTexture(nMapTexture); 

			m_window.draw(nMapSprite); 

			m_window.display();
		}
	}

private:
	void OnCreate()
	{
		int nCellSize = 1;
		m_sizeX = m_sizeX / nCellSize;
		m_sizeY = m_sizeY / nCellSize;
		nOutputSize /= nCellSize; 

		fNoiseSeed1D = new float[nOutputSize]; 
		fPerlinNoise1D = new float[nOutputSize]; 

		fNoiseSeed2D = new float[m_sizeX * m_sizeY];
		fPerlinNoise2D = new float[m_sizeX * m_sizeY];

		for (int i = 0; i < nOutputSize; i++) { fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX; }
		for (int i = 0; i < m_sizeX*m_sizeY; i++) { fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX; }



		m_map.create(m_sizeX, m_sizeY, sf::Color::Black); 
	}

	void OnUpdate()
	{
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			nMode = 1; 
			std::cout << "Clicked 1" << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			nMode = 2;
			std::cout << "Clicked 2" << std::endl;
		}

		if (Keyboard::isKeyPressed(Keyboard::Numpad1))
		{
			nOctavesCount = 1; 
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad2))
		{
			nOctavesCount = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad3))
		{
			nOctavesCount = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad4))
		{
			nOctavesCount = 4;
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad5))
		{
			nOctavesCount = 5;
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad6))
		{
			nOctavesCount = 6;
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad7))
		{
			nOctavesCount = 7;
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad8))
		{
			nOctavesCount = 8;
		}
		if (Keyboard::isKeyPressed(Keyboard::Numpad9))
		{
			nOctavesCount = 9;
		}


		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			fBias += 0.2; 
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			fBias -= 0.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			m_map.saveToFile("PNSC" + std::to_string(nPictureCount) + ".png");
			nPictureCount++; 
		}


		if (nMode == 1)
		{
			if (Keyboard::isKeyPressed(Keyboard::N)) {
				for (int i = 0; i < nOutputSize; i++) fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
			} // Noise Between 0 and +1
		
				

			if (Keyboard::isKeyPressed(Keyboard::M)) {
				for (int i = 0; i < nOutputSize; i++) fNoiseSeed1D[i] = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
			}// Noise Between -1 and +1

			
			ResetGrid(); 
			PerlinNoise1D(nOutputSize, fNoiseSeed1D, nOctavesCount, fBias, fPerlinNoise1D);
			CreateGridFromVector1D();
			
		}

		if (nMode == 2)
		{
			if (Keyboard::isKeyPressed(Keyboard::N)) {
				for (int i = 0; i < m_sizeX*m_sizeY; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
			} // Noise Between 0 and +1



			if (Keyboard::isKeyPressed(Keyboard::M)) {
				for (int i = 0; i < m_sizeX * m_sizeY; i++) fNoiseSeed2D[i] = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
			}// Noise Between -1 and +1


			ResetGrid();
			PerlinNoise2D(m_sizeX, m_sizeY, fNoiseSeed2D, nOctavesCount, fBias, fPerlinNoise2D);
			CreateGridFromVector2D();
		}

	}

	void PerlinNoise1D(int nCount, float* fSeed, int nOctaves, float fBias, float* fOutput)
	{
		// Used 1D Perlin Noise
		for (int x = 0; x < nCount; x++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = nCount >> o;
				int nSample1 = (x / nPitch) * nPitch;
				int nSample2 = (nSample1 + nPitch) % nCount;

				float fBlend = (float)(x - nSample1) / (float)nPitch;

				float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];

				fScaleAcc += fScale;
				fNoise += fSample * fScale;
				fScale = fScale / fBias;
			}

			// Scale to seed range
			fOutput[x] = fNoise / fScaleAcc;
		}
	}

	void PerlinNoise2D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput)
	{
		// Used 1D Perlin Noise
		for (int x = 0; x < nWidth; x++)
			for (int y = 0; y < nHeight; y++)
			{
				float fNoise = 0.0f;
				float fScaleAcc = 0.0f;
				float fScale = 1.0f;

				for (int o = 0; o < nOctaves; o++)
				{
					int nPitch = nWidth >> o;
					int nSampleX1 = (x / nPitch) * nPitch;
					int nSampleY1 = (y / nPitch) * nPitch;

					int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
					int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

					float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
					float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

					float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
					float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

					fScaleAcc += fScale;
					fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
					fScale = fScale / fBias;
				}

				// Scale to seed range
				fOutput[y * nWidth + x] = fNoise / fScaleAcc;
			}

	}


	void CreateGridFromVector2D()
	{
		for (int x = 0; x < m_sizeX; x++) {
			for (int y = 0; y < m_sizeY; y++) {
				int pixel_bw = (int)(fPerlinNoise2D[x * nOutputSize + y] * 8.0f);
				switch (pixel_bw)
				{
				case 0:  m_map.setPixel(x,y,sf::Color::Black); break;
				case 1:  m_map.setPixel(x,y,sf::Color::Blue); break;
				case 2:  m_map.setPixel(x,y,sf::Color::Cyan); break;
				case 3:  m_map.setPixel(x,y,sf::Color::Green); break;
				case 4:  m_map.setPixel(x,y,sf::Color::Green); break;
				case 5:  m_map.setPixel(x,y,sf::Color::Magenta); break;
				case 6:  m_map.setPixel(x,y,sf::Color::Red); break;
				case 7:  m_map.setPixel(x,y,sf::Color::White); break;
				case 8:  m_map.setPixel(x,y,sf::Color::Yellow); break;
				}
			}
		}
	}

	void CreateGridFromVector1D()
	{
		for (int i = 0; i < m_sizeX; i++) {
			int y = -(fPerlinNoise1D[i] * (float)m_sizeX / 2.0f) + (float)m_sizeY / 2.0f;
			if (y < m_sizeX/2)
			{
				for (int j = y; j < m_sizeY/2; j++) {
					m_map.setPixel(i,j,sf::Color::Green); 
				}
			}
			else {
				for (int j = m_sizeY / 2; j <= y; j++) {
					m_map.setPixel(i, j, sf::Color::Red);
				}
			}
		}
	}

	void ResetGrid()
	{
		for (int x = 0; x < m_sizeX; x++) {
			for (int y = 0; y < m_sizeX; y++) {
				m_map.setPixel(x, y, sf::Color::Black); 
			}
		}
	}


private: 
	int m_sizeX = 256, m_sizeY = 256;
	Image m_map; 
	Texture nMapTexture; 
	Sprite nMapSprite; 
	RenderWindow m_window; 


	// 1d
	float* fNoiseSeed1D = nullptr; 
	float* fPerlinNoise1D = nullptr; 

	float* fNoiseSeed2D = nullptr;
	float* fPerlinNoise2D = nullptr; 

	float fBias = 2; 

	int nOctavesCount = 1; 
	int nOutputSize = m_sizeX;

	int nMode; 

	int nPictureCount = 0; 
};