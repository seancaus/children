Rails.application.routes.draw do
	root 'welcome#index'
	get 'welcome/index'

	get 'login', to: 'login#index'
	get 'login/register', to: 'login#register'
	# resources :login
	# For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
