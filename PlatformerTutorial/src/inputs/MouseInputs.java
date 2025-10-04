package inputs;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import gamestates.Gamestate;
import main.GamePanel;

public class MouseInputs implements MouseListener, MouseMotionListener {

    private GamePanel gamePanel;

    public MouseInputs(GamePanel gamePanel) {
        this.gamePanel = gamePanel;
    }

    // Helper method to scale coordinates
    private MouseEvent getScaledMouseEvent(MouseEvent e) {
        int scaledX = (int) (e.getX() / gamePanel.getScaleX());
        int scaledY = (int) (e.getY() / gamePanel.getScaleY());
        return new MouseEvent(e.getComponent(), e.getID(), e.getWhen(), e.getModifiers(),
                              scaledX, scaledY, e.getClickCount(), e.isPopupTrigger(), e.getButton());
    }

    @SuppressWarnings("incomplete-switch")
    @Override
    public void mouseDragged(MouseEvent e) {
        MouseEvent scaledEvent = getScaledMouseEvent(e);
        switch (Gamestate.state) {
            case PLAYING -> gamePanel.getGame().getPlaying().mouseDragged(scaledEvent);
            case OPTIONS -> gamePanel.getGame().getGameOptions().mouseDragged(scaledEvent);
        }
    }

    @SuppressWarnings("incomplete-switch")
    @Override
    public void mouseMoved(MouseEvent e) {
        MouseEvent scaledEvent = getScaledMouseEvent(e);
        switch (Gamestate.state) {
            case MENU -> gamePanel.getGame().getMenu().mouseMoved(scaledEvent);
            case PLAYER_SELECTION -> gamePanel.getGame().getPlayerSelection().mouseMoved(scaledEvent);
            case PLAYING -> gamePanel.getGame().getPlaying().mouseMoved(scaledEvent);
            case OPTIONS -> gamePanel.getGame().getGameOptions().mouseMoved(scaledEvent);
        }
    }

    @SuppressWarnings("incomplete-switch")
    @Override
    public void mouseClicked(MouseEvent e) {
        MouseEvent scaledEvent = getScaledMouseEvent(e);
        switch (Gamestate.state) {
            case PLAYING -> gamePanel.getGame().getPlaying().mouseClicked(scaledEvent);
        }
    }

    @SuppressWarnings("incomplete-switch")
    @Override
    public void mousePressed(MouseEvent e) {
        MouseEvent scaledEvent = getScaledMouseEvent(e);
        switch (Gamestate.state) {
            case MENU -> gamePanel.getGame().getMenu().mousePressed(scaledEvent);
            case PLAYER_SELECTION -> gamePanel.getGame().getPlayerSelection().mousePressed(scaledEvent);
            case PLAYING -> gamePanel.getGame().getPlaying().mousePressed(scaledEvent);
            case OPTIONS -> gamePanel.getGame().getGameOptions().mousePressed(scaledEvent);
        }
    }

    @SuppressWarnings("incomplete-switch")
    @Override
    public void mouseReleased(MouseEvent e) {
        MouseEvent scaledEvent = getScaledMouseEvent(e);
        switch (Gamestate.state) {
            case MENU -> gamePanel.getGame().getMenu().mouseReleased(scaledEvent);
            case PLAYER_SELECTION -> gamePanel.getGame().getPlayerSelection().mouseReleased(scaledEvent);
            case PLAYING -> gamePanel.getGame().getPlaying().mouseReleased(scaledEvent);
            case OPTIONS -> gamePanel.getGame().getGameOptions().mouseReleased(scaledEvent);
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        // Not in use
    }

    @Override
    public void mouseExited(MouseEvent e) {
        // Not in use
    }
}
