#include <SFGUI/Separator.hpp>
#include <SFGUI/Context.hpp>
#include <SFGUI/RenderQueue.hpp>
#include <SFGUI/Engine.hpp>

namespace sfg {

Separator::Separator( Orientation orientation ) :
	m_orientation( orientation )
{
	RequestResize();
}

Separator::Ptr Separator::Create( Orientation orientation ) {
	return Ptr( new Separator( orientation ) );
}

Separator::Orientation Separator::GetOrientation() const {
	return m_orientation;
}


std::unique_ptr<RenderQueue> Separator::InvalidateImpl() const {
	return Context::Get().GetEngine().CreateSeparatorDrawable( std::dynamic_pointer_cast<const Separator>( shared_from_this() ) );
}

sf::Vector2f Separator::CalculateRequisition() {
	return sf::Vector2f( 2.f, 2.f );
}

const std::string& Separator::GetName() const {
	static const std::string name( "Separator" );
	return name;
}

}
