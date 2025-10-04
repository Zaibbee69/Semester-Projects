package main;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;
import inputs.KeyboardInputs;
import inputs.MouseInputs;
import static main.Game.GAME_HEIGHT;
import static main.Game.GAME_WIDTH;

public class GamePanel extends JPanel {

	private MouseInputs mouseInputs;
	private Game game;

	public GamePanel(Game game) {
		mouseInputs = new MouseInputs(this);
		this.game = game;
		setPanelSize();
		addKeyListener(new KeyboardInputs(this));
		addMouseListener(mouseInputs);
		addMouseMotionListener(mouseInputs);
		setDoubleBuffered(true);

	}

	private void setPanelSize() {
		Dimension size = new Dimension(GAME_WIDTH, GAME_HEIGHT);
		setPreferredSize(size);
	}

	public void updateGame() {

	}

	@Override
	public void paintComponent(Graphics g) {
	    super.paintComponent(g);
	    Graphics2D g2d = (Graphics2D) g;

	    // Scale game render to fit screen
	    double scaleX = getWidth() / (double) Game.GAME_WIDTH;
	    double scaleY = getHeight() / (double) Game.GAME_HEIGHT;
	    double scale = Math.min(scaleX, scaleY);

	    g2d.scale(scale, scale);
	    game.render(g2d);

	    g2d.dispose();
	}


	public Game getGame() {
		return game;
	}
	
	public double getScaleX() {
	    return getWidth() / (double) Game.GAME_WIDTH;
	}

	public double getScaleY() {
	    return getHeight() / (double) Game.GAME_HEIGHT;
	}


}